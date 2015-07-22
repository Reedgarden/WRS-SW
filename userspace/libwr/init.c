/* Step-by-step switch hardware initialization */

#include <stdio.h>
#include <stdlib.h>

#include <libwr/switch_hw.h>
#include "i2c_sfp.h"
#include <libwr/shw_io.h>
#include <libwr/wrs-msg.h>

int shw_init()
{
	pr_info("%s\n======================================================\n",
		__TIME__);

	/* Init input/output (GPIO & CPU I2C) */
	assert_init(shw_io_init());

	/* Map the the FPGA memory space */
	assert_init(shw_fpga_mmap_init());

	/* Configure all (GPIO & CPU I2C) */
	shw_io_configure_all();

	/* Initialize SFP Buses (FPGA I2C) */
	assert_init(shw_sfp_buses_init());

	/* Init the SFP GPIO */
	shw_sfp_gpio_init();

	/* Init the FANs */
	assert_init(shw_init_fans());

	pr_info("HW initialization done!\n");
	return 0;
}

int shw_exit_fatal(void)
{
	pr_error("exiting due to fatal error.\n");
	exit(-1);
}
