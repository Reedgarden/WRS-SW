/*
 * Note: this file originally auto-generated by mib2c using
 *  : generic-table-enums.m2c 12526 2005-07-15 22:41:16Z rstory $
 *
 * $Id:$
 */
#ifndef IEEE8021BRIDGEBASETABLE_ENUMS_H
#define IEEE8021BRIDGEBASETABLE_ENUMS_H

#ifdef __cplusplus
extern "C" {
#endif

 /*
 * NOTES on enums
 * ==============
 *
 * Value Mapping
 * -------------
 * If the values for your data type don't exactly match the
 * possible values defined by the mib, you should map them
 * below. For example, a boolean flag (1/0) is usually represented
 * as a TruthValue in a MIB, which maps to the values (1/2).
 *
 */
/*************************************************************************
 *************************************************************************
 *
 * enum definitions for table ieee8021BridgeBaseTable
 *
 *************************************************************************
 *************************************************************************/

/*************************************************************
 * constants for enums for the MIB node
 * ieee8021BridgeBaseComponentType (INTEGER / ASN_INTEGER)
 *
 * since a Textual Convention may be referenced more than once in a
 * MIB, protect againt redefinitions of the enum values.
 */
#ifndef IEEE8021BRIDGEBASECOMPONENTTYPE_ENUMS
#define IEEE8021BRIDGEBASECOMPONENTTYPE_ENUMS

#define IEEE8021BRIDGEBASECOMPONENTTYPE_ICOMPONENT  1
#define IEEE8021BRIDGEBASECOMPONENTTYPE_BCOMPONENT  2
#define IEEE8021BRIDGEBASECOMPONENTTYPE_CVLANCOMPONENT  3
#define IEEE8021BRIDGEBASECOMPONENTTYPE_SVLANCOMPONENT  4
#define IEEE8021BRIDGEBASECOMPONENTTYPE_DBRIDGECOMPONENT  5

#endif /* IEEE8021BRIDGEBASECOMPONENTTYPE_ENUMS */


/*************************************************************
 * constants for enums for the MIB node
 * ieee8021BridgeBaseDeviceCapabilities (BITS / ASN_OCTET_STR)
 *
 * since a Textual Convention may be referenced more than once in a
 * MIB, protect againt redefinitions of the enum values.
 */
#ifndef IEEE8021BRIDGEBASEDEVICECAPABILITIES_ENUMS
#define IEEE8021BRIDGEBASEDEVICECAPABILITIES_ENUMS

#define IEEE8021BRIDGEBASEDEVICECAPABILITIES_DOT1DEXTENDEDFILTERINGSERVICES_FLAG  (1 << (7-0))
#define IEEE8021BRIDGEBASEDEVICECAPABILITIES_DOT1DTRAFFICCLASSES_FLAG  (1 << (7-1))
#define IEEE8021BRIDGEBASEDEVICECAPABILITIES_DOT1QSTATICENTRYINDIVIDUALPORT_FLAG  (1 << (7-2))
#define IEEE8021BRIDGEBASEDEVICECAPABILITIES_DOT1QIVLCAPABLE_FLAG  (1 << (7-3))
#define IEEE8021BRIDGEBASEDEVICECAPABILITIES_DOT1QSVLCAPABLE_FLAG  (1 << (7-4))
#define IEEE8021BRIDGEBASEDEVICECAPABILITIES_DOT1QHYBRIDCAPABLE_FLAG  (1 << (7-5))
#define IEEE8021BRIDGEBASEDEVICECAPABILITIES_DOT1QCONFIGURABLEPVIDTAGGING_FLAG  (1 << (7-6))
#define IEEE8021BRIDGEBASEDEVICECAPABILITIES_DOT1DLOCALVLANCAPABLE_FLAG  (1 << (7-7))

#endif /* IEEE8021BRIDGEBASEDEVICECAPABILITIES_ENUMS */

/* TODO: WR: Review this flag as further development be done. For now
   it's hardcoded but it should be read from some configuration file */
#define IEEE8021BRIDGEBASEDEVICECAPABILITIES_FLAG \
        (IEEE8021BRIDGEBASEDEVICECAPABILITIES_DOT1DTRAFFICCLASSES_FLAG | \
         IEEE8021BRIDGEBASEDEVICECAPABILITIES_DOT1QSTATICENTRYINDIVIDUALPORT_FLAG | \
         IEEE8021BRIDGEBASEDEVICECAPABILITIES_DOT1QSVLCAPABLE_FLAG | \
         IEEE8021BRIDGEBASEDEVICECAPABILITIES_DOT1QCONFIGURABLEPVIDTAGGING_FLAG)


/*************************************************************
 * constants for enums for the MIB node
 * ieee8021BridgeBaseTrafficClassesEnabled (TruthValue / ASN_INTEGER)
 *
 * since a Textual Convention may be referenced more than once in a
 * MIB, protect againt redefinitions of the enum values.
 */
#ifndef TRUTHVALUE_ENUMS
#define TRUTHVALUE_ENUMS

#define TRUTHVALUE_TRUE  1
#define TRUTHVALUE_FALSE  2

#endif /* TRUTHVALUE_ENUMS */


/*************************************************************
 * constants for enums for the MIB node
 * ieee8021BridgeBaseMmrpEnabledStatus (TruthValue / ASN_INTEGER)
 *
 * since a Textual Convention may be referenced more than once in a
 * MIB, protect againt redefinitions of the enum values.
 */
#ifndef TRUTHVALUE_ENUMS
#define TRUTHVALUE_ENUMS

#define TRUTHVALUE_TRUE  1
#define TRUTHVALUE_FALSE  2

#endif /* TRUTHVALUE_ENUMS */


/*************************************************************
 * constants for enums for the MIB node
 * ieee8021BridgeBaseRowStatus (RowStatus / ASN_INTEGER)
 *
 * since a Textual Convention may be referenced more than once in a
 * MIB, protect againt redefinitions of the enum values.
 */
#ifndef ROWSTATUS_ENUMS
#define ROWSTATUS_ENUMS

#define ROWSTATUS_ACTIVE  1
#define ROWSTATUS_NOTINSERVICE  2
#define ROWSTATUS_NOTREADY  3
#define ROWSTATUS_CREATEANDGO  4
#define ROWSTATUS_CREATEANDWAIT  5
#define ROWSTATUS_DESTROY  6

#endif /* ROWSTATUS_ENUMS */




#ifdef __cplusplus
}
#endif

#endif /* IEEE8021BRIDGEBASETABLE_ENUMS_H */
