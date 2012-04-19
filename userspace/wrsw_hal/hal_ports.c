/* Port initialization and state machine */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <linux/if.h>

//#include <wr_ipc.h>

/* LOTs of hardware includes */
#include <hw/trace.h>
#include <hw/hpll.h>
#include <hw/dmpll.h>
#include <hw/phy_calibration.h>
#include <hw/pio.h>
#include <hw/pio_pins.h>
#include <hw/fpga_regs.h>
#include <hw/endpoint_regs.h>
#include <hw/watchdog.h>

#include "wrsw_hal.h"
#include "hal_exports.h"
#include "driver_stuff.h"

#define MAX_PORTS 64

/* Port modes - WR Uplink/Downlink/Non-WR-at-all */
#define HAL_PORT_MODE_WR_UPLINK 1
#define HAL_PORT_MODE_WR_DOWNLINK 2
#define HAL_PORT_MODE_NON_WR 3

/* Port state machine states */
#define HAL_PORT_STATE_LINK_DOWN 1
#define HAL_PORT_STATE_UP 2
#define HAL_PORT_STATE_CALIBRATION 3
#define HAL_PORT_STATE_LOCKING 4

/* Locking state machine states */
#define LOCK_STATE_NONE 0
#define LOCK_STATE_WAIT_HPLL 1
#define LOCK_STATE_WAIT_DMPLL 2
#define LOCK_STATE_LOCKED 3
#define LOCK_STATE_START 4

/* Default fiber alpha coefficient (G.652 @ 1310 nm TX / 1550 nm RX) */
#define DEFAULT_FIBER_ALPHA_COEF (1.4682e-04*1.76)

/* LED location masks - uplink LEDs are on the front-panel, downlink LEDs are in the mini-backplane
and so they are accessed in different way by the CPU. */
#define LED_DOWN_MASK 0x00
#define LED_UP_MASK 0x80


/* Internal port state structure */
typedef struct {
/* non-zero: allocated */
	int in_use;
/* linux i/f name */
	char name[16];

/* MAC addr */
	uint8_t hw_addr[6];

/* ioctl() hw index */
	int hw_index;

/* file descriptor for ioctls() */
	int fd;
	int hw_addr_auto;

/* port timing mode (HAL_PORT_MODE_xxxx) */
	int mode;

/* port FSM state (HAL_PORT_STATE_xxxx) */
	int state;

/* unused */
	int index;

/* 1: PLL is locked to this port */	
	int locked;
	
/* calibration data */
	hal_port_calibration_t calib;

/* current DMTD loopback phase (picoseconds) and whether is it valid or not */
	uint32_t phase_val;
	int phase_val_valid;
	int tx_cal_pending, rx_cal_pending;
/* locking FSM state */
	int lock_state;

/* Endpoint's base address */
	uint32_t ep_base;
} hal_port_state_t;


/* Port table */
static hal_port_state_t ports[MAX_PORTS];

/* An fd of always opened raw sockets for ioctl()-ing Ethernet devices */
static int fd_raw;

/* generates a unique MAC address for port if_name (currently produced from the MAC of the
   management port). */
/* FIXME: MAC addresses should be kept in some EEPROM */
static int get_mac_address(const char *if_name, uint8_t *mac_addr)
{
	struct ifreq ifr;
	int idx;
	int uniq_num;

	sscanf(if_name, "wr%d", &idx); 

	strncpy(ifr.ifr_name, "eth0", sizeof(ifr.ifr_name));

	if(ioctl(fd_raw, SIOCGIFHWADDR, &ifr) < 0)
		return -1;

	uniq_num = (int)ifr.ifr_hwaddr.sa_data[4] * 256 + (int)ifr.ifr_hwaddr.sa_data[5] + idx;

	mac_addr[0] = 0x2; // locally administered MAC
	mac_addr[1] = 0x4a;
	mac_addr[2] = 0xbc;
	mac_addr[3] = (uniq_num >> 16) & 0xff;
	mac_addr[4] = (uniq_num >> 8) & 0xff;
	mac_addr[5] = uniq_num & 0xff;

	return 0;
}

/* Resets the state variables of a particular port and re-starts its state machines */
static void reset_port_state(hal_port_state_t *p)
{
	p->calib.rx_calibrated = 0;
	p->calib.tx_calibrated = 0;
	p->locked = 0;
	p->state = HAL_PORT_STATE_LINK_DOWN;
	p->lock_state = LOCK_STATE_NONE;
	p->tx_cal_pending = 0;
	p->rx_cal_pending = 0;
}

#define AT_INT32 0
#define AT_DOUBLE 1

/* helper function for retreiving port parameters from the config files with type checking and defaulting
   to a given value when the parameter is not found */
static void cfg_get_port_param(const char *port_name, const char *param_name, void *rval, int param_type, ...)
{
	va_list ap;

	char str[1024];
	snprintf(str, sizeof(str), "ports.%s.%s", port_name, param_name);

	va_start(ap, param_type);

	switch(param_type)
	{
	case AT_INT32:
		if(hal_config_get_int(str, (int *) rval))
			*(int *) rval = va_arg(ap, int);
		break;

	case AT_DOUBLE:
		if(hal_config_get_double(str, (double *) rval))
			*(double *) rval = va_arg(ap, double);
		break;

	default:
		break;

	}
	va_end(ap);
}


/* checks if the port is supported by the FPGA firmware */
static int check_port_presence(const char *if_name)
{
	struct ifreq ifr;

	strncpy(ifr.ifr_name, if_name, sizeof(ifr.ifr_name));

	if(ioctl(fd_raw, SIOCGIFHWADDR, &ifr) < 0)
		return -1;

	return 0;
}

/* Performs one-time TX path calibration for a certain port, right after the HAL startup
   (TX latency never changes as long as the TLK1221 PHY reference clock is enabled, 
   even if the link goes down) */

/* No more calibration in V3 */

/* Port initialization. Assigns the MAC address, WR timing mode, reads parameters from the config file. */
int hal_init_port(const char *name, int index)
{
	char key_name[128];
	char val[128];
	char cmd[128];
	hal_port_state_t *p = &ports[index];

	uint8_t mac_addr[6];

/* check if the port is compiled into the firmware, if not, just ignore it. */
	if(check_port_presence(name) < 0)
	{
		reset_port_state(p);
		p->in_use = 0;
		return 0;
	}

/* make sure the states and other port variables are in their initial state */
	reset_port_state(p);

	p->in_use = 1;

/* generate a (hopefully) unique MAC */
	get_mac_address(name, mac_addr);

	TRACE(TRACE_INFO,"Initializing port '%s' [%02x:%02x:%02x:%02x:%02x:%02x]", name, mac_addr[0],  mac_addr[1],  mac_addr[2],  mac_addr[3],  mac_addr[4],  mac_addr[5] );

	strncpy(p->name, name, 16);
	memcpy(p->hw_addr, mac_addr, 6);

/* ... and assign it to the port */
	snprintf(cmd, sizeof(cmd), "/sbin/ifconfig %s hw ether %02x:%02x:%02x:%02x:%02x:%02x", name, mac_addr[0],  mac_addr[1],  mac_addr[2],  mac_addr[3],  mac_addr[4],  mac_addr[5] );
	system(cmd);

	snprintf(cmd, sizeof(cmd), "/sbin/ifconfig %s up", name);
	system(cmd);

/* read calibraton parameters (unwrapping and constant deltas) */
	cfg_get_port_param(name, "phy_rx_min",   &p->calib.phy_rx_min,   AT_INT32, 18*800);
	cfg_get_port_param(name, "phy_tx_min",   &p->calib.phy_tx_min,    AT_INT32, 18*800);

	cfg_get_port_param(name, "delta_tx_sfp",  &p->calib.delta_tx_sfp,  AT_INT32, 0);
	cfg_get_port_param(name, "delta_rx_sfp",  &p->calib.delta_rx_sfp,  AT_INT32, 0);

	cfg_get_port_param(name, "delta_tx_board",  &p->calib.delta_tx_board,  AT_INT32, 0);
	cfg_get_port_param(name, "delta_rx_board",  &p->calib.delta_rx_board,  AT_INT32, 0);

/* read the alpha parameter and turn it into a format suitable for the PTPd */
	cfg_get_port_param(name, "fiber_alpha", &p->calib.fiber_alpha, AT_DOUBLE, DEFAULT_FIBER_ALPHA_COEF);

/* WARNING! when alpha = 1.0 (no asymmetry), fiber_fix_alpha = 0! */
	p->calib.fiber_fix_alpha = (double)pow(2.0, 40.0) * ((p->calib.fiber_alpha + 1.0) / (p->calib.fiber_alpha + 2.0) - 0.5);


	sscanf(p->name+2, "%d", &p->hw_index);


/* Set up the endpoint's base address (fixme: do this with the driver) */

/* FIXME: this address should come from the driver header */
	p->ep_base = 0x30000 + 0x400  *  p->hw_index;

/* Configure the port's timing role depending on the contents of the config file */
	snprintf(key_name, sizeof(key_name),  "ports.%s.mode", p->name);

	if(!hal_config_get_string(key_name, val, sizeof(val)))
	{
		if(!strcasecmp(val, "wr_m_and_s"))
			p->mode = HEXP_PORT_MODE_WR_M_AND_S; 
		else if(!strcasecmp(val, "wr_master"))
			p->mode = HEXP_PORT_MODE_WR_MASTER;
		else if(!strcasecmp(val, "wr_slave"))
			p->mode = HEXP_PORT_MODE_WR_SLAVE;
		else if(!strcasecmp(val, "non_wr"))
			p->mode = HEXP_PORT_MODE_NON_WR;
		else {
			TRACE(TRACE_ERROR,"Invalid mode specified for port %s. Defaulting to Non-WR", p->name);
			p->mode = HEXP_PORT_MODE_NON_WR;
		}

		TRACE(TRACE_INFO,"Port %s: mode %s", p->name, val);
/* nothing in the config file? Disable WR mode */
	} else {
		p->mode = HEXP_PORT_MODE_NON_WR;
	}

/* Used to pre-calibrate the TX path for each port. No more in V3 */

	return 0;
}

/* Interates via all the ports defined in the config file and intializes them one after another. */
int hal_init_ports()
{

	int index = 0;
	char port_name[128];

	TRACE(TRACE_INFO, "Initializing switch ports");

/* Open a single raw socket for accessing the MAC addresses, etc. */
	fd_raw = socket(AF_PACKET, SOCK_DGRAM, 0);
	if(fd_raw < 0) return -1;

	memset(ports, 0, sizeof(ports));

	for(;;)
	{
		if(!hal_config_iterate("ports", index++, port_name, sizeof(port_name))) break;
		hal_init_port(port_name, index);
	}

	return 0;
}

/* Checks if the link is up on inteface (if_name). Returns non-zero if yes. */
static int check_link_up(const char *if_name)
{
	struct ifreq ifr;

	strncpy(ifr.ifr_name, if_name, sizeof(ifr.ifr_name));

	if(ioctl(fd_raw, SIOCGIFFLAGS, &ifr) > 0) return -1;

	return (ifr.ifr_flags & IFF_UP && ifr.ifr_flags & IFF_RUNNING);
}


/* Port locking state machine - controls the HPLL/DMPLL. 
   TODO (v3): get rid of this code - this will all be moved to the realtime CPU inside the FPGA
   and the softpll. */
static void port_locking_fsm(hal_port_state_t *p)
{
}

/* Updates the current value of the phase shift on a given port. Called by the main update function regularly. */
struct wr_phase_req{
	int valid;
	uint32_t phase;
};

static void poll_dmtd(hal_port_state_t *p)
{
	struct ifreq ifr;
	struct wr_phase_req preq;
	
	strncpy(ifr.ifr_name, p->name, sizeof(ifr.ifr_name));

	ifr.ifr_data=  (void *)&preq;

	if(ioctl(fd_raw, PRIV_IOCGGETPHASE, &ifr) < 0) return;
	
//	fprintf(stderr, "Poll: %d %d\n", preq.valid, preq.phase);
	
	/* FIXME: what should we do here? */
	p->phase_val = (int)((double)preq.phase / 16384.0 * 16000.0);
	p->phase_val_valid = preq.valid;
}

uint32_t pcs_readl(hal_port_state_t *p, int reg)
{
	struct ifreq ifr;
	uint32_t rv;
	
	strncpy(ifr.ifr_name, p->name, sizeof(ifr.ifr_name));

	rv = NIC_READ_PHY_CMD(reg);
	ifr.ifr_data = (void *)&rv;
//	printf("raw fd %d name %s\n", fd_raw, ifr.ifr_name);
	if(	ioctl(fd_raw, PRIV_IOCPHYREG, &ifr) < 0)
	{
		fprintf(stderr,"ioctl failed\n");
	};
	
	printf("PCS_readl: reg %d data %x\n", reg, NIC_RESULT_DATA(rv));
	return NIC_RESULT_DATA(rv);
}


/* Calibration state machine */
static void calibration_fsm(hal_port_state_t *p)
{


}


/* Main port state machine */
static void port_fsm(hal_port_state_t *p)
{
	int link_up = check_link_up(p->name);

/* If, at any moment, the link goes down, reset the FSM and the port state structure. */
	if(!link_up && p->state != HAL_PORT_STATE_LINK_DOWN)
	{
		if(p->locked) 
			; /* nothing: was hpll_switch_reference(local) */
		TRACE(TRACE_INFO, "%s: link down", p->name);
		p->state = HAL_PORT_STATE_LINK_DOWN;
		reset_port_state(p);

		p->calib.rx_calibrated = 0;
		return;
	}

/* handle the locking part */
	port_locking_fsm(p);

	switch(p->state)
	{

/* Default state - wait until the link goes up */
	case HAL_PORT_STATE_LINK_DOWN:
	{
		if(link_up)
		{
		p->calib.tx_calibrated = 1;
		p->calib.rx_calibrated = 1;
		/* FIXME: use proper register names */
		p->calib.delta_rx_phy = p->calib.phy_rx_min + ((pcs_readl(p, 16) >> 4) & 0x1f) * 800;
		p->calib.delta_tx_phy = p->calib.phy_tx_min;

		TRACE(TRACE_INFO,"Bypassing calibration for downlink port %s [dTx %d, dRx %d]", p->name, p->calib.delta_tx_phy, 	p->calib.delta_rx_phy);

		p->tx_cal_pending = 0;
		p->rx_cal_pending = 0;

			TRACE(TRACE_INFO, "%s: link up", p->name);
			p->state = HAL_PORT_STATE_UP;
		}
		break;
	}

/* Default "on" state - just keep polling the phase value. */
	case HAL_PORT_STATE_UP:
		poll_dmtd(p);

		break;

/* Locking state (entered upon calling hal_port_start_lock()). */
	case HAL_PORT_STATE_LOCKING:

/* Once the locking FSM is done, go back to the "UP" state. */
		if(p->locked)
		{
			TRACE(TRACE_INFO,"[main-fsm] Port %s locked.", p->name);
			p->state = HAL_PORT_STATE_UP;
		}

		break;

/* Calibration state (entered by starting the calibration with halexp_calibration_cmd()) */
	case HAL_PORT_STATE_CALIBRATION:

/* Calibration still pending - if not anymore, go back to the "UP" state */
		if(p->rx_cal_pending || p->tx_cal_pending)
			calibration_fsm(p);
		else
			p->state = HAL_PORT_STATE_UP;


		break;
	}
}

/* Executes the port FSM for all ports. Called regularly by the main loop. */
void hal_update_ports()
{
	int i;
	for(i=0; i<MAX_PORTS;i++)
		if(ports[i].in_use)
			port_fsm(&ports[i]);
}

/* Queries the port state structre for a given network interface. */
static hal_port_state_t *lookup_port(const char *name)
{
	int i;
	for(i = 0; i< MAX_PORTS;i++)
		if(ports[i].in_use && !strcmp(name, ports[i].name))
			return &ports[i];

	return NULL;
}

/* Triggers the locking state machine, called by the PTPd during the WR link setup phase. */
int hal_port_start_lock(const char  *port_name, int priority)
{
	hal_port_state_t *p = lookup_port(port_name);

	if(!p) return PORT_ERROR;

/* can't lock to a disconnected port */
	if(p->state != HAL_PORT_STATE_UP)
		return PORT_BUSY;

/* fixme: check the main FSM state before */
	p->state = HAL_PORT_STATE_LOCKING;
	p->lock_state = LOCK_STATE_START;

	TRACE(TRACE_INFO, "Locking to port: %s", port_name);

	return PORT_OK;
}


/* Returns 1 if the port is locked */
int hal_port_check_lock(const char  *port_name)
{
	hal_port_state_t *p = lookup_port(port_name);

	if(!p) return PORT_ERROR;
	if(p->lock_state == LOCK_STATE_LOCKED)
		return 1;

	return 0;
}

/* Public function for querying the state of a particular port (DMTD phase, calibration deltas, etc.) */
int halexp_get_port_state(hexp_port_state_t *state, const char *port_name)
{
	hal_port_state_t *p = lookup_port(port_name);
	if(!p)
		return -1;


	state->valid = 1;
	state->mode = p->mode;
	state->up = p->state != HAL_PORT_STATE_LINK_DOWN;
	state->is_locked = p->lock_state == LOCK_STATE_LOCKED;
	state->phase_val = p->phase_val;
	state->phase_val_valid = p->phase_val_valid;

	state->tx_calibrated = p->calib.tx_calibrated;
	state->rx_calibrated = p->calib.rx_calibrated;

	state->delta_tx = p->calib.delta_tx_phy + p->calib.delta_tx_sfp + p->calib.delta_tx_board;
	state->delta_rx = p->calib.delta_rx_phy + p->calib.delta_rx_sfp + p->calib.delta_rx_board;

	state->t2_phase_transition = 6000;
	state->t4_phase_transition = 6000;
	state->clock_period = 16000;
	state->fiber_fix_alpha = p->calib.fiber_fix_alpha;

	memcpy(state->hw_addr, p->hw_addr, 6);
	state->hw_index = p->hw_index;

	return 0;
}

/* Returns 1 if any of the switch's ports is currently being calibrated */
static int any_port_calibrating()
{
	int i;
	for(i=0; i<MAX_PORTS;i++)
		if(ports[i].state == HAL_PORT_STATE_CALIBRATION && ports[i].in_use)
			return 1;

	return 0;
}

/* Public function for controlling the calibration process. Called by the PTPd during WR Link setup. */

/* No more calibration in V3 */

/* Public API function - returns the array of names of all WR network interfaces */
int halexp_query_ports(hexp_port_list_t *list)
{
	int i;
	int n = 0;

	TRACE(TRACE_INFO," client queried port list.");

	for(i=0; i<MAX_PORTS;i++)
	{
		if(ports[i].in_use)
			strcpy(list->port_names[n++], ports[i].name);
	}

	list->num_ports = n;
	return 0;
}

/* Maciek's ptpx export for checking the presence of the external 10 MHz ref clock */
int hal_extsrc_check_lock()
{
	return -1;
/*
	return -1; //<0 - there is no external source lock
	return 1; //>0 - we are locked to an external source
	return 0; //=0 - HW problem, wait
*/	
}
