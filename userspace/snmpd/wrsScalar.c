/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.scalar.conf 17798 2009-10-27 06:44:54Z magfr $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "wrsSnmp.h"

#include <stdint.h>
static uint32_t fakeStatValue;

static int
handle_wrsScalarOne(netsnmp_mib_handler *handler,
                    netsnmp_handler_registration *reginfo,
                    netsnmp_agent_request_info *reqinfo,
                    netsnmp_request_info *requests)
{
    int             ret;
    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    switch (reqinfo->mode) {

    case MODE_GET:
        fakeStatValue++;
        snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                 &fakeStatValue,
                                 sizeof(fakeStatValue));
        break;

        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
    case MODE_SET_RESERVE1:
        /*
         * or you could use netsnmp_check_vb_type_and_size instead 
         */
        ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
        if (ret != SNMP_ERR_NOERROR) {
            netsnmp_set_request_error(reqinfo, requests, ret);
        }
        break;

    case MODE_SET_RESERVE2:
    case MODE_SET_FREE:
        break;

    case MODE_SET_ACTION:
        /* FIXME: set... */
        break;

    case MODE_SET_COMMIT:
        /* FIXME: commit */
        break;

    case MODE_SET_UNDO:
        /* FIXME: undo */
        break;

    default:
        /*
         * we should never get here, so this is a really bad error 
         */
        snmp_log(LOG_ERR, "unknown mode (%d) in handle_wrsScalarOne\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

/** Initializes the wrsScalar module */
void
init_wrsScalar(void)
{
    const oid wrsScalarOne_oid[] = { WRS_OID, 1 };

    DEBUGMSGTL(("wrsScalar", "Initializing\n"));

    netsnmp_register_scalar(netsnmp_create_handler_registration
                            ("wrsScalarOne", handle_wrsScalarOne,
                             wrsScalarOne_oid,
                             OID_LENGTH(wrsScalarOne_oid),
                             HANDLER_CAN_RWRITE));
}

