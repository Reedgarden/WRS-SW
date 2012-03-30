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

#ifndef IEEE8021BRIDGETPPORTTABLE_OIDS_H
#define IEEE8021BRIDGETPPORTTABLE_OIDS_H

#ifdef __cplusplus
extern "C" {
#endif


/* column number definitions for table ieee8021BridgeTpPortTable */
#define IEEE8021BRIDGETPPORTTABLE_OID              1,3,111,2,802,1,1,2,1,2,1


#define COLUMN_IEEE8021BRIDGETPPORTCOMPONENTID         1

#define COLUMN_IEEE8021BRIDGETPPORT         2

#define COLUMN_IEEE8021BRIDGETPPORTMAXINFO         3
#define COLUMN_IEEE8021BRIDGETPPORTMAXINFO_FLAG    (0x1 << 0)

#define COLUMN_IEEE8021BRIDGETPPORTINFRAMES         4
#define COLUMN_IEEE8021BRIDGETPPORTINFRAMES_FLAG    (0x1 << 1)

#define COLUMN_IEEE8021BRIDGETPPORTOUTFRAMES         5
#define COLUMN_IEEE8021BRIDGETPPORTOUTFRAMES_FLAG    (0x1 << 2)

#define COLUMN_IEEE8021BRIDGETPPORTINDISCARDS         6
#define COLUMN_IEEE8021BRIDGETPPORTINDISCARDS_FLAG    (0x1 << 3)


#define IEEE8021BRIDGETPPORTTABLE_MIN_COL   COLUMN_IEEE8021BRIDGETPPORTMAXINFO
#define IEEE8021BRIDGETPPORTTABLE_MAX_COL   COLUMN_IEEE8021BRIDGETPPORTINDISCARDS

/* Applicable columns for dummy ports */
#define IEEE8021BRIDGETPPORTTABLE_DUMMY_PORTS_COLS \
                    COLUMN_IEEE8021BRIDGETPPORTMAXINFO_FLAG



#ifdef __cplusplus
}
#endif

#endif /* IEEE8021BRIDGETPPORTTABLE_OIDS_H */
