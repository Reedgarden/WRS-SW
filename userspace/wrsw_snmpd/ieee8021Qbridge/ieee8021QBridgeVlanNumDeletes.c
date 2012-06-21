/*
 * White Rabbit Switch Management
 * Copyright (C) 2010, CERN.
 *
 * Version:     wrsw_snmpd v1.0
 *
 * Authors:     Juan Luis Manas (juan.manas@integrasys.es)
 *
 * Description: Handles requests for ieee8021QBridgeVlanNumDeletes scalar.
 *              Provides support for inserting/deleting static unicast
 *              entries into the RTU filtering database
 *              Note: this file originally auto-generated by mib2c using
 *              : mib2c.scalar.conf 17337 2009-01-01 14:28:29Z magfr $
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
#include "ieee8021QBridgeVlanNumDeletes.h"

#include "rtu_fd_proxy.h"
#include "utils.h"

/**
 * Initializes the ieee8021QBridgeVlanNumDeletes module
 */
void init_ieee8021QBridgeVlanNumDeletes(void)
{
    const oid _oid[] = {1,3,111,2,802,1,1,4,1,4,1};

    rtu_fdb_proxy_init("rtu_fdb");
    netsnmp_register_scalar(
        netsnmp_create_handler_registration(
            "ieee8021QBridgeVlanNumDeletes",
            handle_ieee8021QBridgeVlanNumDeletes,
            (oid *)_oid,
            OID_LENGTH(_oid),
            HANDLER_CAN_RONLY
        )
    );
    snmp_log(LOG_INFO, "%s: initialised\n", __FILE__);
}

int handle_ieee8021QBridgeVlanNumDeletes(
        netsnmp_mib_handler          *handler,
        netsnmp_handler_registration *reginfo,
        netsnmp_agent_request_info   *reqinfo,
        netsnmp_request_info         *requests)
{
    uint64_t num_deletes;
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    switch(reqinfo->mode) {
    case MODE_GET:
        
        num_deletes = rtu_fdb_proxy_get_num_vlan_deletes();
        if (errno)
            goto error;
        snmp_set_var_typed_value(requests->requestvb, ASN_COUNTER64,
            (u_char *)&num_deletes, sizeof(num_deletes));
        break;
    default:
        snmp_log(LOG_ERR, "%s: unknown mode (%d) in handle\n", __FILE__,
            reqinfo->mode);
        return SNMP_ERR_GENERR;
    }
    return SNMP_ERR_NOERROR;

error:
    snmp_log(LOG_ERR, "%s: mini-ipc error [%s]\n", __FILE__, strerror(errno));
    return SNMP_ERR_GENERR;
}
