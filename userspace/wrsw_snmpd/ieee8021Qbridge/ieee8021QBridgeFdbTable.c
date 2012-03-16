/*
 * White Rabbit Switch Management
 * Copyright (C) 2010, CERN.
 *
 * Version:     wrsw_snmpd v1.0
 *
 * Authors:     Juan Luis Manas (juan.manas@integrasys.es)
 *
 * Description: Handles requests for ieee8021QBridgeFdbTable table.
 *              Provides configuration information and basic control
 *              on the RTU filtering database.
 *              Note: this file originally auto-generated by mib2c using
 *              : mib2c.raw-table.conf 17436 2009-03-31 15:12:19Z dts12 $
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include "ieee8021QBridgeFdbTable.h"
#include "rtu_fd_proxy.h"
#include "utils.h"

#define MIBMOD  "8021Q"

/* column number definitions for table ieee8021QBridgeFdbTable */
#define COLUMN_IEEE8021QBRIDGEFDBCOMPONENTID		    1
#define COLUMN_IEEE8021QBRIDGEFDBID		                2
#define COLUMN_IEEE8021QBRIDGEFDBDYNAMICCOUNT		    3
#define COLUMN_IEEE8021QBRIDGEFDBLEARNEDENTRYDISCARDS	4
#define COLUMN_IEEE8021QBRIDGEFDBAGINGTIME		        5

static int get_column(netsnmp_variable_list *vb, int colnum, u_long fid)
{
    u_long   count;       // ieee8021QBridgeFdbDynamicCount
    uint64_t discards;    // ieee8021QBridgeFdbLearnedEntryDiscards
    long     age;         // ieee8021QBridgeFdbAgingTime

    errno = 0;
    switch (colnum) {
    case COLUMN_IEEE8021QBRIDGEFDBDYNAMICCOUNT:
        count = rtu_fdb_proxy_get_num_dynamic_entries(fid);
        if (errno)
            return SNMP_ERR_GENERR;
        snmp_set_var_typed_integer(vb, ASN_GAUGE, count);
        break;
    case COLUMN_IEEE8021QBRIDGEFDBLEARNEDENTRYDISCARDS:
        discards = rtu_fdb_proxy_get_num_learned_entry_discards(fid);
        if (errno)
            return SNMP_ERR_GENERR;
        snmp_set_var_typed_value(vb, ASN_COUNTER64, (u_char *)&discards,
                                 sizeof(discards));
        break;
    case COLUMN_IEEE8021QBRIDGEFDBAGINGTIME:
        age = rtu_fdb_proxy_get_aging_time(fid);
        if (errno)
            return SNMP_ERR_GENERR;
        snmp_set_var_typed_integer(vb, ASN_INTEGER, age);
        break;
    default:
        return SNMP_NOSUCHOBJECT;
    }
    return SNMP_ERR_NOERROR;
}

static int get(netsnmp_request_info *req)
{
    netsnmp_table_request_info  *tinfo;
    u_long cid;         // ieee8021QBridgeFdbComponentId
    u_long fid;         // ieee8021QBridgeFdbId

    // Get indexes from request
    tinfo = netsnmp_extract_table_info(req);
    if (!tinfo || !tinfo->indexes)
        return SNMP_ERR_GENERR;

    cid = *tinfo->indexes->val.integer;
    fid = *tinfo->indexes->next_variable->val.integer;

    DEBUGMSGTL((MIBMOD, "cid=%d fid=%d column=%d\n", cid, fid, tinfo->colnum));

    if ((cid != DEFAULT_COMPONENT_ID) ||
        (fid >= NUM_FIDS))
        return SNMP_NOSUCHINSTANCE;

    // return entry column value
    return get_column(req->requestvb, tinfo->colnum, fid);
}

static int get_next(netsnmp_request_info         *req,
                    netsnmp_handler_registration *reginfo)
{
    u_long cid;
    u_long fid;
    int oid_len, rootoid_len;
    netsnmp_table_request_info  *tinfo = netsnmp_extract_table_info(req);

    // Get indexes from request - in case OID contains them!.
    // Otherwise use default values for first row.
    oid_len     = req->requestvb->name_length;
    rootoid_len = reginfo->rootoid_len;

    if (oid_len > rootoid_len) {
        if (!tinfo || !tinfo->indexes)
            return SNMP_ERR_GENERR;
        cid = *tinfo->indexes->val.integer;
    } else {
        cid = 0;
    }

    fid = (oid_len > rootoid_len + 1) ?
          *tinfo->indexes->next_variable->val.integer:0;

    DEBUGMSGTL((MIBMOD, "cid=%d fid =%d column=%d\n", cid, fid, tinfo->colnum));

    // Get index for next entry - SNMP_ENDOFMIBVIEW informs the handler
    // to proceed with next column.
    if (cid > DEFAULT_COMPONENT_ID)
        return SNMP_ENDOFMIBVIEW;
    if (cid == 0) {
        cid = DEFAULT_COMPONENT_ID;
        fid = 0;
    } else {
        if (fid >= NUM_FIDS)
            return SNMP_ENDOFMIBVIEW;
        errno = 0;
        fid = rtu_fdb_proxy_get_next_fid(fid);
        if (errno)
            return SNMP_ERR_GENERR;
        if (fid >= NUM_FIDS)
            return SNMP_ENDOFMIBVIEW;
    }

    // Update indexes and OID returned in SNMP response
    *tinfo->indexes->val.integer = cid;
    *tinfo->indexes->next_variable->val.integer = fid;
    update_oid(req, reginfo, tinfo->colnum, tinfo->indexes);

    // return next entry column value
    return get_column(req->requestvb, tinfo->colnum, fid);
}

static int set_reserve1(netsnmp_request_info *req)
{
    int ret;
    u_long cid;
    u_long fid;
    netsnmp_table_request_info *tinfo;

    // Get indexes from request
    tinfo = netsnmp_extract_table_info(req);
    if (!tinfo || !tinfo->indexes)
        return SNMP_ERR_GENERR;

    cid = *tinfo->indexes->val.integer;
    fid = *tinfo->indexes->next_variable->val.integer;

    DEBUGMSGTL((MIBMOD, "cid=%d fid =%d column=%d\n", cid, fid, tinfo->colnum));

    // Check indexes
    if ((cid != DEFAULT_COMPONENT_ID) ||
        (fid >= NUM_FIDS))
        return SNMP_NOSUCHINSTANCE;

    // Check column value
    switch (tinfo->colnum) {
    case COLUMN_IEEE8021QBRIDGEFDBAGINGTIME:
        ret = netsnmp_check_vb_int_range(
            req->requestvb, MIN_AGING_TIME, MAX_AGING_TIME);
        break;
    default:
        return SNMP_ERR_NOTWRITABLE;
    }
    return ret;
}

static int set_commit(netsnmp_request_info *req)
{
    netsnmp_table_request_info *tinfo;
    u_long age;
    u_long fid;
    int err;

    // At this point values are already checked by set_reserve1 so fdb method
    // should not fail. Mini-ipc should also not fail... otherwise we have a
    // problem, ...but  exactly the same problem that would exist in case we
    // implement the two phase commit, as undoing also requires mini-ipc calls.
    tinfo = netsnmp_extract_table_info(req);
    fid = *tinfo->indexes->next_variable->val.integer;
    switch (tinfo->colnum) {
    case COLUMN_IEEE8021QBRIDGEFDBAGINGTIME:
        age = *req->requestvb->val.integer;
        errno = 0;
        err = rtu_fdb_proxy_set_aging_time(fid, age);
        if (errno) {
            snmp_log(LOG_ERR, "%s(%s): mini-ipc error [%s]\n",
                __FILE__, __func__, strerror(errno));
            return SNMP_ERR_GENERR;
        }
        if (err) {
            snmp_log(LOG_ERR, "%s(%s): set aging time error [%d]\n",
                __FILE__, __func__, err);
            return SNMP_ERR_GENERR;
        }
        break;
    }
    return SNMP_ERR_NOERROR;
}

/**
 * handles requests for the ieee8021QBridgeFdbTable table
 */
static int _handler(netsnmp_mib_handler          *handler,
                    netsnmp_handler_registration *reginfo,
                    netsnmp_agent_request_info   *reqinfo,
                    netsnmp_request_info         *requests)
{
    netsnmp_request_info *req;
    int err;

    switch (reqinfo->mode) {
    case MODE_GET:
        for (req = requests; req; req = req->next) {
            err = get(req);
            if (err)
                netsnmp_set_request_error(reqinfo, req, err);
        }
        break;
    case MODE_GETNEXT:
        for (req = requests; req; req = req->next) {
            err = get_next(req, reginfo);
            if (err)
                netsnmp_set_request_error(reqinfo, req, err);
        }
        break;
    case MODE_SET_RESERVE1:
        for (req=requests; req; req=req->next) {
            err = set_reserve1(req);
            if (err)
                netsnmp_set_request_error(reqinfo, req, err);
        }
        break;
    case MODE_SET_COMMIT:
        for (req = requests; req; req = req->next) {
            err = set_commit(req);
            if (err)
                netsnmp_set_request_error(reqinfo, req, err);
        }
        break;
    }
    return SNMP_ERR_NOERROR;
}

/**
 * Initialize the ieee8021QBridgeFdbTable table by defining its contents and
 * how it's structured
 */
static void initialize_table(void)
{
    const oid _oid[] = {1,3,111,2,802,1,1,4,1,2,1};
    netsnmp_handler_registration    *reg;
    netsnmp_table_registration_info *tinfo;

    reg = netsnmp_create_handler_registration(
            "ieee8021QBridgeFdbTable",
            _handler,
            (oid *)_oid,
            OID_LENGTH(_oid),
            HANDLER_CAN_RWRITE);

    tinfo = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    netsnmp_table_helper_add_indexes(
            tinfo,
            ASN_UNSIGNED,  /* index: ieee8021QBridgeFdbComponentId */
            ASN_UNSIGNED,  /* index: ieee8021QBridgeFdbId */
            0);

    tinfo->min_column = COLUMN_IEEE8021QBRIDGEFDBDYNAMICCOUNT;
    tinfo->max_column = COLUMN_IEEE8021QBRIDGEFDBAGINGTIME;

    netsnmp_register_table(reg, tinfo);
}

/**
 * Initializes the ieee8021QBridgeFdbTable module
 */
void init_ieee8021QBridgeFdbTable(void)
{
    struct minipc_ch *client;

    client = rtu_fdb_proxy_create("rtu_fdb");
    if(client) {
        initialize_table();
        snmp_log(LOG_INFO, "%s: initialised\n", __FILE__);
    } else {
        snmp_log(LOG_ERR, "%s: error creating mini-ipc proxy - %s\n", __FILE__,
            strerror(errno));
    }
}
