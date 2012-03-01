/*
 * White Rabbit Switch CLI (Command Line Interface)
 * Copyright (C) 2011, CERN.
 *
 * Authors:     Miguel Baizan   (miguel.baizan@integrasys.es)
 *              Juan Luis Manas (juan.manas@integrasys.es)
 *
 * Description: Implementation of the commands family 'no'.
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

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "cli_commands.h"
#include "cli_commands_utils.h"

enum no_cmds {
    CMD_NO = 0,
    CMD_NO_CAM,
    CMD_NO_CAM_UNICAST,
    CMD_NO_CAM_UNICAST_VLAN,
    CMD_NO_CAM_MULTICAST,
    CMD_NO_CAM_MULTICAST_VLAN,
    CMD_NO_VLAN,
    NUM_NO_CMDS
};

/* Helper function to remove the static entries in the FDB (both
    unicast or multicast, depending on the OID passed as argument) */
static void del_cam_static_entry(int argc, char **argv, char *base_oid)
{
    oid _oid[MAX_OID_LEN];
    size_t length_oid; /* Base OID length */
    char *addr;
    unsigned int mac[ETH_ALEN];
    int vid;
    int i;


    /* Check that we have the two arguments */
    if (argc != 2) {
        printf("\tError. You have missed some argument\n");
        return;
    }

    /* Parse the MAC address */
    addr = argv[0];
    if (sscanf(addr, "%02x:%02x:%02x:%02x:%02x:%02x",
        &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]) != 6) {
        printf("\tError. Wrong MAC address format. Try: XX:XX:XX:XX:XX:XX\n");
        return;
    }

    /* Check the syntax of the vlan argument */
    for (i = 0; argv[1][i]; i++) {
        if (!isdigit(argv[1][i])) {
            printf("\tError. Only decimal values are allowed\n");
            return;
        }
    }
    if ((atoi(argv[1]) < 0) || (atoi(argv[1]) > (MAX_VID + 1))) {
        printf("\tError. Allowed values are in the range 0 to %d\n",
                (MAX_VID + 1));
        return;
    }
    vid = atoi(argv[1]);

    memset(_oid, 0 , MAX_OID_LEN * sizeof(oid));

    /* Parse the base_oid string to an oid array type */
    length_oid = MAX_OID_LEN;
    if (!snmp_parse_oid(base_oid, _oid, &length_oid))
        return;

    /* Build the indexes */
    _oid[13] = 1;                /* Component ID column */
    _oid[14] = vid;              /* VID column */
    for (i = 15; i < 21 ; i++)   /* MAC address columns */
        _oid[i] = mac[i-15];
    _oid[21] = 0;                /* Receive Port column */

    length_oid += 9;

    /* Row status (delete = 6) */
    cli_snmp_set_int(_oid, length_oid, "6", 'i');

    return;
}

/**
 * \brief Command 'no mac-address-table unicast <MAC Addrress> vlan <VID>'.
 * This command deletes a unicast static entry in the FDB.
 * @param cli CLI interpreter.
 * @param argc number of arguments. Only two arguments allowed.
 * @param agv Two arguments must be specified: the MAC Address (formatted as
 * XX:XX:XX:XX:XX:XX) and the VLAN number (a decimal number between 0 and
 * MAX_VID+1).
 */
void cli_cmd_del_cam_uni_entry(struct cli_shell *cli, int argc, char **argv)
{
    del_cam_static_entry(argc, argv, ".1.3.111.2.802.1.1.4.1.3.1.1.8");
    return;
}

/**
 * \brief Command 'no mac-address-table multicast <MAC Addrress> vlan <VID>'.
 * This command deletes a multicast static entry in the FDB.
 * @param cli CLI interpreter.
 * @param argc number of arguments. Only two arguments allowed.
 * @param agv Two arguments must be specified: the MAC Address (formatted as
 * XX:XX:XX:XX:XX:XX) and the VLAN number (a decimal number between 0 and
 * MAX_VID+1).
 */
void cli_cmd_del_cam_multi_entry(struct cli_shell *cli, int argc, char **argv)
{
    del_cam_static_entry(argc, argv, ".1.3.111.2.802.1.1.4.1.3.2.1.6");
    return;
}

/**
 * \brief Command 'no vlan <VID>'.
 * This command removes a VLAN.
 * @param cli CLI interpreter.
 * @param argc number of arguments. Only one argument allowed.
 * @param agv One argument must be specified: the VLAN number (a decimal
 * number between 0 and MAX_VID+1).
 */
void cli_cmd_del_vlan(struct cli_shell *cli, int argc, char **argv)
{
    oid _oid[MAX_OID_LEN];
    char *base_oid = "1.3.111.2.802.1.1.4.1.4.3.1.7";
    size_t length_oid; /* Base OID length */
    int vid;
    int i;


    /* Check that we have the three arguments */
    if (argc != 1) {
        printf("\tError. You have missed some argument\n");
        return;
    }

    /* Check the syntax of the vlan argument */
    for (i = 0; argv[0][i]; i++) {
        if (!isdigit(argv[0][i])) {
            printf("\tError. Only decimal values are allowed\n");
            return;
        }
    }
    if ((atoi(argv[0]) < 0) || (atoi(argv[0]) > (MAX_VID + 1))) {
        printf("\tError. Allowed values are in the range 0 to %d\n",
                (MAX_VID + 1));
        return;
    }
    vid = atoi(argv[0]);

    memset(_oid, 0 , MAX_OID_LEN * sizeof(oid));

    /* Parse the base_oid string to an oid array type */
    length_oid = MAX_OID_LEN;
    if (!snmp_parse_oid(base_oid, _oid, &length_oid))
        return;

    /* Build the indexes */
    _oid[13] = 1;                /* Component ID column */
    _oid[14] = vid;              /* VID column */

    length_oid += 2;

    /* Row status (delete = 6) */
    cli_snmp_set_int(_oid, length_oid, "6", 'i');

    return;
}

/* Define the 'no' commands family */
struct cli_cmd cli_no[NUM_NO_CMDS] = {
    /* no */
    [CMD_NO] = {
        .parent     = NULL,
        .name       = "no",
        .handler    = NULL,
        .desc       = "Use 'no' to delete/disable some configured parameters",
        .opt        = CMD_NO_ARG,
        .opt_desc   = NULL
    },
    /* no mac-address-table */
    [CMD_NO_CAM] = {
        .parent     = cli_no + CMD_NO,
        .name       = "mac-address-table",
        .handler    = NULL,
        .desc       = "Removes static entries from the filtering database",
        .opt        = CMD_NO_ARG,
        .opt_desc   = NULL
    },
    /* no mac-address-table unicast <MAC Addrress> */
    [CMD_NO_CAM_UNICAST] = {
        .parent     = cli_no + CMD_NO_CAM,
        .name       = "unicast",
        .handler    = NULL,
        .desc       = "Removes a static unicast entry from the filtering"
                      " database",
        .opt        = CMD_ARG_MANDATORY,
        .opt_desc   = "<MAC Addrress> MAC Address"
    },
    /* no mac-address-table unicast <MAC Addrress> vlan <VID> */
    [CMD_NO_CAM_UNICAST_VLAN] = {
        .parent     = cli_no + CMD_NO_CAM_UNICAST,
        .name       = "vlan",
        .handler    = cli_cmd_del_cam_uni_entry,
        .desc       = "Removes a static unicast entry from the filtering"
                      " database",
        .opt        = CMD_ARG_MANDATORY,
        .opt_desc   = "<VID> VLAN number"
    },
    /* no mac-address-table multicast <MAC Addrress> */
    [CMD_NO_CAM_MULTICAST] = {
        .parent     = cli_no + CMD_NO_CAM,
        .name       = "multicast",
        .handler    = NULL,
        .desc       = "Removes a static multicast entry from the filtering"
                      " database",
        .opt        = CMD_ARG_MANDATORY,
        .opt_desc   = "<MAC Addrress> MAC Address"
    },
    /* no mac-address-table multicast <MAC Addrress> vlan <VID> */
    [CMD_NO_CAM_MULTICAST_VLAN] = {
        .parent     = cli_no + CMD_NO_CAM_MULTICAST,
        .name       = "vlan",
        .handler    = cli_cmd_del_cam_multi_entry,
        .desc       = "Removes a static multicast entry from the filtering"
                      " database",
        .opt        = CMD_ARG_MANDATORY,
        .opt_desc   = "<VID> VLAN number"
    },
    /* no vlan <VID> */
    [CMD_NO_VLAN] = {
        .parent     = cli_no + CMD_NO,
        .name       = "vlan",
        .handler    = cli_cmd_del_vlan,
        .desc       = "Removes a VLAN",
        .opt        = CMD_ARG_MANDATORY,
        .opt_desc   = "<VID> VLAN number"
    }
};

/**
 * \brief Init function for the command family 'no'.
 * @param cli CLI interpreter.
 */
void cmd_no_init(struct cli_shell *cli)
{
    int i;

    for (i = 0; i < NUM_NO_CMDS; i++)
        cli_insert_command(cli, &cli_no[i]);
}
