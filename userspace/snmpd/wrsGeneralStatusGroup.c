#include "wrsSnmp.h"
#include "snmp_shmem.h"
#include "wrsCurrentTimeGroup.h"
#include "wrsOSStatusGroup.h"
#include "wrsPortStatusTable.h"
#include "wrsPstatsTable.h"
#include "wrsPtpDataTable.h"
#include "wrsStartCntGroup.h"
#include "wrsTemperatureGroup.h"
#include "wrsVersionGroup.h"

#include "wrsGeneralStatusGroup.h"

static struct pickinfo wrsGeneralStatus_pickinfo[] = {
	FIELD(wrsGeneralStatus_s, ASN_INTEGER, wrsMainSystemStatus),
	FIELD(wrsGeneralStatus_s, ASN_INTEGER, wrsOSStatus),
};

struct wrsGeneralStatus_s wrsGeneralStatus_s;

time_t wrsGeneralStatus_data_fill(void)
{
	static time_t time_update; /* time of last update */
	time_t time_osstatus; /* time when wrsOSStatus data was updated */
	struct wrsOSStatus_s *o;

	time_osstatus = wrsOSStatus_data_fill();

	if (time_osstatus <= time_update) {
		/* cache not updated, return last update time */
		snmp_log(LOG_ERR,
			"SNMP: wrsGeneralStatusGroup cache\n");
		return time_update;
	}

	/*********************************************************************\
	|**************************** wrsOSStatus ****************************|
	\*********************************************************************/
	o = &wrsOSStatus_s;
	if ( /* check if error */
		o->wrsBootSuccessful == WRS_BOOT_SUCCESSFUL_ERROR
	) {
		wrsGeneralStatus_s.wrsOSStatus = WRS_OS_STATUS_ERROR;

	} else if ( /* check if warning */
		o->wrsBootSuccessful == WRS_BOOT_SUCCESSFUL_WARNING
		|| o->wrsTemperatureWarning == WRS_TEMPERATURE_WARNING_THOLD_NOT_SET
		|| o->wrsTemperatureWarning == WRS_TEMPERATURE_WARNING_TOO_HIGH
	) { /* warning */
		wrsGeneralStatus_s.wrsOSStatus = WRS_OS_STATUS_WARNING;

	} else if ( /* check if any of fields equal to 0 */
		o->wrsBootSuccessful == WRS_BOOT_SUCCESSFUL_WARNING_NA
		|| o->wrsBootSuccessful == 0
		|| o->wrsTemperatureWarning == 0
	) { /* warning NA */
		wrsGeneralStatus_s.wrsOSStatus = WRS_OS_STATUS_WARNING_NA;

	} else if ( /* check if OK */
		o->wrsBootSuccessful == WRS_BOOT_SUCCESSFUL_OK
		&& o->wrsTemperatureWarning == WRS_TEMPERATURE_WARNING_OK
	) { /* OK */
		wrsGeneralStatus_s.wrsOSStatus = WRS_OS_STATUS_OK;

	} else { /* probably bug in previous conditions,
		  * this should never happen */
		wrsGeneralStatus_s.wrsOSStatus = WRS_OS_STATUS_BUG;
	}

	time_update = time(NULL);
	wrsCurrentTime_data_fill();
	wrsOSStatus_data_fill();
	wrsPortStatusTable_data_fill(NULL);
	wrsPstatsTable_data_fill(NULL);
	wrsPtpDataTable_data_fill(NULL);
	wrsStartCnt_data_fill();
	wrsVersion_data_fill();

	/*memset(&wrsGeneralStatus_s, 0, sizeof(wrsGeneralStatus_s));*/
	wrsGeneralStatus_s.wrsMainSystemStatus++;
	/* there was an update, return current time */
	return time_update;
}

#define GT_OID WRSGENERALSTATUS_OID
#define GT_PICKINFO wrsGeneralStatus_pickinfo
#define GT_DATA_FILL_FUNC wrsGeneralStatus_data_fill
#define GT_DATA_STRUCT wrsGeneralStatus_s
#define GT_GROUP_NAME "wrsGeneralStatusGroup"
#define GT_INIT_FUNC init_wrsGeneralStatusGroup

#include "wrsGroupTemplate.h"
