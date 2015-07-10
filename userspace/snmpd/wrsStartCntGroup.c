#include "wrsSnmp.h"
#include "snmp_shmem.h"
#include "wrsStartCntGroup.h"

#define START_CNT_SSHD "/tmp/start_cnt_sshd"
#define START_CNT_HTTPD "/tmp/start_cnt_httpd"
#define START_CNT_SNMPD "/tmp/start_cnt_snmpd"
#define START_CNT_SYSLOGD "/tmp/start_cnt_syslogd"
#define START_CNT_WRSWATCHDOG "/tmp/start_cnt_wrs_watchdog"

static struct pickinfo wrsStartCnt_pickinfo[] = {
	FIELD(wrsStartCnt_s, ASN_COUNTER, wrsStartCntHAL),
	FIELD(wrsStartCnt_s, ASN_COUNTER, wrsStartCntPPSI),
	FIELD(wrsStartCnt_s, ASN_COUNTER, wrsStartCntRTUd),
	FIELD(wrsStartCnt_s, ASN_COUNTER, wrsStartCntSshd),
	FIELD(wrsStartCnt_s, ASN_COUNTER, wrsStartCntHttpd),
	FIELD(wrsStartCnt_s, ASN_COUNTER, wrsStartCntSnmpd),
	FIELD(wrsStartCnt_s, ASN_COUNTER, wrsStartCntSyslogd),
	FIELD(wrsStartCnt_s, ASN_COUNTER, wrsStartCntWrsWatchdog),
};

struct wrsStartCnt_s wrsStartCnt_s;

/* read start counter from files in /tmp */
static void read_start_count(char *file, uint32_t *counter)
{
	FILE *f;

	f = fopen(file, "r");
	if (!f) {
		snmp_log(LOG_ERR, "SNMP: wrsStartCntGroup filed to open file "
			 "%s\n", file);
	} else {
		/* ignore fscanf errors */
		fscanf(f, "%d", counter);
		fclose(f);
	}
}

time_t wrsStartCnt_data_fill(void){
	static time_t time_update;
	time_t time_cur;


	time_cur = time(NULL);
	if (time_update
	    && time_cur - time_update < WRSSTARTCNT_CACHE_TIMEOUT) {
		/* cache not updated, return last update time */
		return time_update;
	}
	time_update = time_cur;

	memset(&wrsStartCnt_s, 0, sizeof(wrsStartCnt_s));

	/* get start counters from shmem's */
	wrsStartCnt_s.wrsStartCntHAL = hal_head->pidsequence;
	wrsStartCnt_s.wrsStartCntPPSI = ppsi_head->pidsequence;
	wrsStartCnt_s.wrsStartCntRTUd = rtud_head->pidsequence;

	read_start_count(START_CNT_SSHD, &wrsStartCnt_s.wrsStartCntSshd);
	read_start_count(START_CNT_HTTPD, &wrsStartCnt_s.wrsStartCntHttpd);
	read_start_count(START_CNT_SNMPD, &wrsStartCnt_s.wrsStartCntSnmpd);
	read_start_count(START_CNT_SYSLOGD, &wrsStartCnt_s.wrsStartCntSyslogd);
	read_start_count(START_CNT_WRSWATCHDOG, &wrsStartCnt_s.wrsStartCntWrsWatchdog);

	/* there was an update, return current time */
	return time_update;
}


#define GT_OID WRSSTARTCNT_OID
#define GT_PICKINFO wrsStartCnt_pickinfo
#define GT_DATA_FILL_FUNC wrsStartCnt_data_fill
#define GT_DATA_STRUCT wrsStartCnt_s
#define GT_GROUP_NAME "wrsStartCntGroup"
#define GT_INIT_FUNC init_wrsStartCntGroup

#include "wrsGroupTemplate.h"
