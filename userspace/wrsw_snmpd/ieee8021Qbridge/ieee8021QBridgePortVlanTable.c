/*
 * Note: this file originally auto-generated by mib2c using
 *  : mib2c.raw-table.conf 17436 2009-03-31 15:12:19Z dts12 $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include "ieee8021QBridgePortVlanTable.h"
#include "rtu.h"
#include "endpoint_hw.h"
#include "utils.h"

#define MIBMOD  "8021Q"

/* column number definitions for table ieee8021QBridgePortVlanTable */
#define COLUMN_IEEE8021QBRIDGEPVID                                  1
#define COLUMN_IEEE8021QBRIDGEPORTACCEPTABLEFRAMETYPES              2
#define COLUMN_IEEE8021QBRIDGEPORTINGRESSFILTERING                  3
#define COLUMN_IEEE8021QBRIDGEPORTMVRPENABLEDSTATUS                 4
#define COLUMN_IEEE8021QBRIDGEPORTMVRPFAILEDREGISTRATIONS           5
#define COLUMN_IEEE8021QBRIDGEPORTMVRPLASTPDUORIGIN                 6
#define COLUMN_IEEE8021QBRIDGEPORTRESTRICTEDVLANREGISTRATION        7

static int get_column(netsnmp_request_info *req, int colnum, u_long port)
{
    u_long pvid; // Port VLAN identifier
    int qmode;   // acceptable frame types

    switch (colnum) {
    case COLUMN_IEEE8021QBRIDGEPVID:
        pvid = ep_hw_get_pvid(port);
        if (pvid < 0)
            return SNMP_ERR_GENERR;
        snmp_set_var_typed_integer(req->requestvb, ASN_UNSIGNED, pvid);
        break;
    case COLUMN_IEEE8021QBRIDGEPORTACCEPTABLEFRAMETYPES:
        qmode = ep_hw_get_qmode(port);
        switch(qmode) {
        case access_port:
            snmp_set_var_typed_integer(req->requestvb, ASN_INTEGER, admitUntaggedAndPriority);
            break;
        case trunk_port:
            snmp_set_var_typed_integer(req->requestvb, ASN_INTEGER, admitTagged);
            break;
        case unqualified_port:
            snmp_set_var_typed_integer(req->requestvb, ASN_INTEGER, admitAll);
            break;
        default:
            return SNMP_ERR_GENERR;
        }
        break;
    case COLUMN_IEEE8021QBRIDGEPORTINGRESSFILTERING:
        // true. Discard incoming frames for VLANs that do not include this
        // port in its member set (currently _unsupported_ by WR switch)
        // false. Accept all incoming frames
        snmp_set_var_typed_integer(req->requestvb, ASN_INTEGER, TV_FALSE);
        break;
    default:
        return SNMP_NOSUCHOBJECT;
    }
    return SNMP_ERR_NOERROR;
}

static int get(netsnmp_request_info *req)
{
    netsnmp_table_request_info  *tinfo;
    u_long cid;
    u_long port;

    // Get indexes from request
    tinfo = netsnmp_extract_table_info(req);
    cid  = *tinfo->indexes->val.integer;
    port = *tinfo->indexes->next_variable->val.integer;

    DEBUGMSGTL((MIBMOD, "cid=%d port=%d column=%d\n",
        cid, port, tinfo->colnum));

    if (cid != DEFAULT_COMPONENT_ID)
        return SNMP_NOSUCHINSTANCE;

    if (port > MAX_PORT)
        return SNMP_NOSUCHINSTANCE;

    return get_column(req, tinfo->colnum, port);
}

static int get_next(netsnmp_request_info *req,
    netsnmp_handler_registration *reginfo)
{
    u_long cid;         // ieee8021BridgeBasePortComponentId;
    u_long port;        // ieee8021BridgeBasePort;
    netsnmp_table_request_info  *tinfo;
    int oid_len, rootoid_len;

    tinfo = netsnmp_extract_table_info(req);

    // Get indexes from request - in case OID contains them!.
    // Otherwise use default values for first row.
    oid_len     = req->requestvb->name_length;
    rootoid_len = reginfo->rootoid_len;

    // Get indexes for entry
    cid  = (oid_len > rootoid_len) ?
          *tinfo->indexes->val.integer:0;
    port = (oid_len > rootoid_len + 1) ?
          *tinfo->indexes->next_variable->val.integer:MIN_PORT;

    DEBUGMSGTL((MIBMOD, "cid=%d port=%d column=%d\n",
        cid, port, tinfo->colnum));

    // Get index for next entry - SNMP_ENDOFMIBVIEW informs the handler
    // to proceed with next column.
    if (cid > DEFAULT_COMPONENT_ID) {
        return SNMP_ENDOFMIBVIEW;
    } else if (cid == 0) {
        cid = DEFAULT_COMPONENT_ID;
        port = MIN_PORT;
    } else {
        if (++port > MAX_PORT)
            return SNMP_ENDOFMIBVIEW;
    }

    // Update indexes and OID returned in SNMP response
    *tinfo->indexes->val.integer = cid;
    *tinfo->indexes->next_variable->val.integer = port;
    update_oid(req, reginfo, tinfo->colnum, tinfo->indexes);

    // return next entry column value
    return get_column(req, tinfo->colnum, port);
}

static int set_reserve1(netsnmp_request_info *req)
{
    int ret = SNMP_ERR_NOERROR;
    netsnmp_table_request_info *tinfo;
    u_long cid;                 // ieee8021BridgeBasePortComponentId;
    u_long port;                // ieee8021BridgeBasePort;

    tinfo = netsnmp_extract_table_info(req);
    // Check indexes
    cid = *tinfo->indexes->val.integer;
    if (cid != DEFAULT_COMPONENT_ID)
        return SNMP_NOSUCHINSTANCE;

    port = *tinfo->indexes->next_variable->val.integer;
    if (port > MAX_PORT)
        return SNMP_NOSUCHINSTANCE;

    // Check column value
    switch (tinfo->colnum) {
    case COLUMN_IEEE8021QBRIDGEPVID:
        ret = netsnmp_check_vb_int_range(req->requestvb, MIN_PVID, MAX_PVID);
        break;
    case COLUMN_IEEE8021QBRIDGEPORTACCEPTABLEFRAMETYPES:
        ret = netsnmp_check_vb_int_range(req->requestvb, admitAll, admitTagged);
        break;
    default:
        return SNMP_ERR_NOTWRITABLE;
    }
    return ret;
}

static int set_commit(netsnmp_request_info *req)
{
    int qmode;
    netsnmp_table_request_info *tinfo;
    u_long port;                    // ieee8021BridgeBasePort;
    u_long pvid;                    // ieee8021QBridgePvid
    long acceptable_frame_types;    // ieee8021QBridgePortAcceptableFrameTypes
    long port_ingress_filtering;    // ieee8021QBridgePortIngressFiltering
    int err = SNMP_ERR_NOERROR;

    tinfo = netsnmp_extract_table_info(req);
    port = *tinfo->indexes->next_variable->val.integer;
    switch (tinfo->colnum) {
    case COLUMN_IEEE8021QBRIDGEPVID:
        pvid = *req->requestvb->val.integer;
        err = ep_hw_set_pvid(port, pvid);
        if (err == -EIO)
            return SNMP_ERR_GENERR;
        break;
    case COLUMN_IEEE8021QBRIDGEPORTACCEPTABLEFRAMETYPES:
        acceptable_frame_types = *req->requestvb->val.integer;
        switch(acceptable_frame_types) {
        case admitAll:
            ep_hw_set_qmode(port, unqualified_port);
            break;
        case admitUntaggedAndPriority:
            ep_hw_set_qmode(port, access_port);
            break;
        case admitTagged:
            ep_hw_set_qmode(port, trunk_port);
            break;
        }
        break;
    }
    return err;
}


/**
 * Handles requests for the ieee8021QBridgePortVlanTable table
 */
static int _handler(
    netsnmp_mib_handler           *handler,
    netsnmp_handler_registration  *reginfo,
    netsnmp_agent_request_info    *reqinfo,
    netsnmp_request_info          *requests)
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
            if (err) {
                netsnmp_set_request_error(reqinfo, req, err);
                return SNMP_ERR_NOERROR;
            }
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
 * Initialize the ieee8021QBridgePortVlanTable table by defining its
 * contents and how it's structured
 */
static void initialize_table(void)
{
    const oid _oid[] = {1,3,111,2,802,1,1,4,1,4,5};
    netsnmp_handler_registration    *reg;
    netsnmp_table_registration_info *tinfo;

    reg = netsnmp_create_handler_registration(
            "ieee8021QBridgePortVlanTable",
            _handler,
            (oid *)_oid,
            OID_LENGTH(_oid),
            HANDLER_CAN_RWRITE);

    tinfo = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    netsnmp_table_helper_add_indexes(
            tinfo,
            ASN_UNSIGNED,  /* index: ieee8021BridgeBasePortComponentId */
            ASN_UNSIGNED,  /* index: ieee8021BridgeBasePort */
            0);

    tinfo->min_column = COLUMN_IEEE8021QBRIDGEPVID;
    tinfo->max_column = COLUMN_IEEE8021QBRIDGEPORTRESTRICTEDVLANREGISTRATION;

    netsnmp_register_table(reg, tinfo);
}

/**
 * Initializes the ieee8021QBridgePortVlanTable module
 */
void init_ieee8021QBridgePortVlanTable(void)
{
    int err;

    err = ep_hw_init();
    if (err) {
        snmp_log(LOG_ERR, "%s: error on NIC driver init - %s\n", __FILE__,
            strerror(err));
    } else {
        initialize_table();
        snmp_log(LOG_INFO, "%s: initialised\n", __FILE__);
    }
}
