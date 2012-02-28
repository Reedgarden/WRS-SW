/*
 * White Rabbit SNMP
 * Copyright (C) 2010, CERN.
 *
 * Version:     wrsw_snmpd v1.0
 *
 * Authors:     Miguel Baizán (miguel.baizan@integrasys-sa.com)
 *
 * Description: OIDs definition.
 *              Note: this file originally auto-generated by mib2c using
 *              mib2c.mfd.conf 17337
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

#ifndef IEEE8021BRIDGEBASETABLE_OIDS_H
#define IEEE8021BRIDGEBASETABLE_OIDS_H

#ifdef __cplusplus
extern "C" {
#endif


/* column number definitions for table ieee8021BridgeBaseTable */
#define IEEE8021BRIDGEBASETABLE_OID              1,3,111,2,802,1,1,2,1,1,1


#define COLUMN_IEEE8021BRIDGEBASECOMPONENTID         1

#define COLUMN_IEEE8021BRIDGEBASEBRIDGEADDRESS         2
#define COLUMN_IEEE8021BRIDGEBASEBRIDGEADDRESS_FLAG    (0x1 << 0)

#define COLUMN_IEEE8021BRIDGEBASENUMPORTS         3
#define COLUMN_IEEE8021BRIDGEBASENUMPORTS_FLAG    (0x1 << 1)

#define COLUMN_IEEE8021BRIDGEBASECOMPONENTTYPE         4
#define COLUMN_IEEE8021BRIDGEBASECOMPONENTTYPE_FLAG    (0x1 << 2)

#define COLUMN_IEEE8021BRIDGEBASEDEVICECAPABILITIES         5
#define COLUMN_IEEE8021BRIDGEBASEDEVICECAPABILITIES_FLAG    (0x1 << 3)

#define COLUMN_IEEE8021BRIDGEBASETRAFFICCLASSESENABLED         6
#define COLUMN_IEEE8021BRIDGEBASETRAFFICCLASSESENABLED_FLAG    (0x1 << 4)

#define COLUMN_IEEE8021BRIDGEBASEMMRPENABLEDSTATUS         7
#define COLUMN_IEEE8021BRIDGEBASEMMRPENABLEDSTATUS_FLAG    (0x1 << 5)

#define COLUMN_IEEE8021BRIDGEBASEROWSTATUS         8
#define COLUMN_IEEE8021BRIDGEBASEROWSTATUS_FLAG    (0x1 << 6)


#define IEEE8021BRIDGEBASETABLE_MIN_COL   COLUMN_IEEE8021BRIDGEBASEBRIDGEADDRESS
#define IEEE8021BRIDGEBASETABLE_MAX_COL   COLUMN_IEEE8021BRIDGEBASEROWSTATUS


    /*
     * TODO:405:r: Review IEEE8021BRIDGEBASETABLE_SETTABLE_COLS macro.
     * OR together all the writable cols.
     */
#define IEEE8021BRIDGEBASETABLE_SETTABLE_COLS (COLUMN_IEEE8021BRIDGEBASEBRIDGEADDRESS_FLAG | COLUMN_IEEE8021BRIDGEBASENUMPORTS_FLAG | COLUMN_IEEE8021BRIDGEBASECOMPONENTTYPE_FLAG | COLUMN_IEEE8021BRIDGEBASEDEVICECAPABILITIES_FLAG | COLUMN_IEEE8021BRIDGEBASETRAFFICCLASSESENABLED_FLAG | COLUMN_IEEE8021BRIDGEBASEMMRPENABLEDSTATUS_FLAG | COLUMN_IEEE8021BRIDGEBASEROWSTATUS_FLAG)
    /*
     * TODO:405:r: Review IEEE8021BRIDGEBASETABLE_REQUIRED_COLS macro.
     * OR together all the required rows for row creation.
     * default is writable cols w/out defaults.
     */
#define IEEE8021BRIDGEBASETABLE_REQUIRED_COLS (COLUMN_IEEE8021BRIDGEBASEBRIDGEADDRESS_FLAG | COLUMN_IEEE8021BRIDGEBASECOMPONENTTYPE_FLAG | COLUMN_IEEE8021BRIDGEBASEDEVICECAPABILITIES_FLAG | COLUMN_IEEE8021BRIDGEBASEROWSTATUS_FLAG)

/* Temporary mask to control what columns we want to implement */
#define COLUMNS_IMPLEMENTED \
                (COLUMN_IEEE8021BRIDGEBASEBRIDGEADDRESS_FLAG | \
                 COLUMN_IEEE8021BRIDGEBASENUMPORTS_FLAG | \
                 COLUMN_IEEE8021BRIDGEBASECOMPONENTTYPE_FLAG | \
                 COLUMN_IEEE8021BRIDGEBASEDEVICECAPABILITIES_FLAG | \
                 COLUMN_IEEE8021BRIDGEBASETRAFFICCLASSESENABLED_FLAG | \
                 COLUMN_IEEE8021BRIDGEBASEROWSTATUS_FLAG)

#ifdef __cplusplus
}
#endif

#endif /* IEEE8021BRIDGEBASETABLE_OIDS_H */