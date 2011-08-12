/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 12088 $ of $
 *
 * $Id:$
 */
/* standard Net-SNMP includes */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/* include our parent header */
#include "ieee8021BridgeBasePortTable.h"


/** @defgroup data_get data_get: Routines to get data
 *
 * TODO:230:M: Implement ieee8021BridgeBasePortTable get routines.
 * TODO:240:M: Implement ieee8021BridgeBasePortTable mapping routines (if any).
 *
 * These routine are used to get the value for individual objects. The
 * row context is passed, along with a pointer to the memory where the
 * value should be copied.
 *
 * @{
 */
/**********************************************************************
 **********************************************************************
 ***
 *** Table ieee8021BridgeBasePortTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * IEEE8021-BRIDGE-MIB::ieee8021BridgeBasePortTable is subid 4 of ieee8021BridgeBase.
 * Its status is Current.
 * OID: .1.3.111.2.802.1.1.2.1.1.4, length: 11
*/

/* ---------------------------------------------------------------------
 * TODO:200:r: Implement ieee8021BridgeBasePortTable data context functions.
 */


/**
 * set mib index(es)
 *
 * @param tbl_idx mib index structure
 * @param ieee8021BridgeBasePortComponentId_val
 * @param ieee8021BridgeBasePort_val
 *
 * @retval MFD_SUCCESS     : success.
 * @retval MFD_ERROR       : other error.
 *
 * @remark
 *  This convenience function is useful for setting all the MIB index
 *  components with a single function call. It is assume that the C values
 *  have already been mapped from their native/rawformat to the MIB format.
 */
int
ieee8021BridgeBasePortTable_indexes_set_tbl_idx(ieee8021BridgeBasePortTable_mib_index *tbl_idx, u_long ieee8021BridgeBasePortComponentId_val, u_long ieee8021BridgeBasePort_val)
{
    DEBUGMSGTL(("verbose:ieee8021BridgeBasePortTable:ieee8021BridgeBasePortTable_indexes_set_tbl_idx","called\n"));

    /* ieee8021BridgeBasePortComponentId(1)/IEEE8021PbbComponentIdentifier/ASN_UNSIGNED/u_long(u_long)//l/a/w/e/R/d/H */
    tbl_idx->ieee8021BridgeBasePortComponentId = ieee8021BridgeBasePortComponentId_val;

    /* ieee8021BridgeBasePort(2)/IEEE8021BridgePortNumber/ASN_UNSIGNED/u_long(u_long)//l/a/w/e/R/d/H */
    tbl_idx->ieee8021BridgeBasePort = ieee8021BridgeBasePort_val;


    return MFD_SUCCESS;
} /* ieee8021BridgeBasePortTable_indexes_set_tbl_idx */

/**
 * @internal
 * set row context indexes
 *
 * @param reqreq_ctx the row context that needs updated indexes
 *
 * @retval MFD_SUCCESS     : success.
 * @retval MFD_ERROR       : other error.
 *
 * @remark
 *  This function sets the mib indexs, then updates the oid indexs
 *  from the mib index.
 */
int
ieee8021BridgeBasePortTable_indexes_set(ieee8021BridgeBasePortTable_rowreq_ctx *rowreq_ctx, u_long ieee8021BridgeBasePortComponentId_val, u_long ieee8021BridgeBasePort_val)
{
    DEBUGMSGTL(("verbose:ieee8021BridgeBasePortTable:ieee8021BridgeBasePortTable_indexes_set","called\n"));

    if(MFD_SUCCESS != ieee8021BridgeBasePortTable_indexes_set_tbl_idx(&rowreq_ctx->tbl_idx
                                   , ieee8021BridgeBasePortComponentId_val
                                   , ieee8021BridgeBasePort_val
           ))
        return MFD_ERROR;

    /*
     * convert mib index to oid index
     */
    rowreq_ctx->oid_idx.len = sizeof(rowreq_ctx->oid_tmp) / sizeof(oid);
    if(0 != ieee8021BridgeBasePortTable_index_to_oid(&rowreq_ctx->oid_idx,
                                    &rowreq_ctx->tbl_idx)) {
        return MFD_ERROR;
    }

    return MFD_SUCCESS;
} /* ieee8021BridgeBasePortTable_indexes_set */


/*---------------------------------------------------------------------
 * IEEE8021-BRIDGE-MIB::ieee8021BridgeBasePortEntry.ieee8021BridgeBasePortIfIndex
 * ieee8021BridgeBasePortIfIndex is subid 3 of ieee8021BridgeBasePortEntry.
 * Its status is Current, and its access level is ReadWrite.
 * OID: .1.3.111.2.802.1.1.2.1.1.4.1.3
 * Description:
The value of the instance of the IfIndex object,
         defined in the IF-MIB, for the interface corresponding
         to this port, or the value 0 if the port has not been
         bound to an underlying frame source and sink.

         It is an implementation specific decision as to whether this object
         may be modified if it has been created or if 0 is a legal value.

         The underlying IfEntry indexed by this column must be persistent
         across reinitializations of the management system.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 1      hashint   1
 *   settable   1
 *   hint: d
 *
 * Ranges:  0 - 2147483647;
 *
 * Its syntax is InterfaceIndexOrZero (based on perltype INTEGER32)
 * The net-snmp type is ASN_INTEGER. The C type decl is long (long)
 */
/**
 * Extract the current value of the ieee8021BridgeBasePortIfIndex data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param ieee8021BridgeBasePortIfIndex_val_ptr
 *        Pointer to storage for a long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
ieee8021BridgeBasePortIfIndex_get( ieee8021BridgeBasePortTable_rowreq_ctx *rowreq_ctx, long * ieee8021BridgeBasePortIfIndex_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != ieee8021BridgeBasePortIfIndex_val_ptr );


    DEBUGMSGTL(("verbose:ieee8021BridgeBasePortTable:ieee8021BridgeBasePortIfIndex_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the ieee8021BridgeBasePortIfIndex data.
 * copy (* ieee8021BridgeBasePortIfIndex_val_ptr ) from rowreq_ctx->data
 */
    (* ieee8021BridgeBasePortIfIndex_val_ptr ) = rowreq_ctx->data.ieee8021BridgeBasePortIfIndex;

    return MFD_SUCCESS;
} /* ieee8021BridgeBasePortIfIndex_get */

/*---------------------------------------------------------------------
 * IEEE8021-BRIDGE-MIB::ieee8021BridgeBasePortEntry.ieee8021BridgeBasePortDelayExceededDiscards
 * ieee8021BridgeBasePortDelayExceededDiscards is subid 4 of ieee8021BridgeBasePortEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.111.2.802.1.1.2.1.1.4.1.4
 * Description:
The number of frames discarded by this port due
        to excessive transit delay through the bridge.  It
        is incremented by both transparent and source
        route bridges.

        Discontinuities in the value of the counter can occur
        at re-initialization of the management system, and at
        other times as indicated by the value of
        ifCounterDiscontinuityTime object of the associated
        interface (if any).
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is COUNTER64 (based on perltype COUNTER64)
 * The net-snmp type is ASN_COUNTER64. The C type decl is U64 (U64)
 */
/**
 * Extract the current value of the ieee8021BridgeBasePortDelayExceededDiscards data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param ieee8021BridgeBasePortDelayExceededDiscards_val_ptr
 *        Pointer to storage for a U64 variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
ieee8021BridgeBasePortDelayExceededDiscards_get( ieee8021BridgeBasePortTable_rowreq_ctx *rowreq_ctx, U64 * ieee8021BridgeBasePortDelayExceededDiscards_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != ieee8021BridgeBasePortDelayExceededDiscards_val_ptr );

/*
 * TODO:231:o: |-> copy ieee8021BridgeBasePortDelayExceededDiscards data.
 * get (* ieee8021BridgeBasePortDelayExceededDiscards_val_ptr ).low and (* ieee8021BridgeBasePortDelayExceededDiscards_val_ptr ).high from rowreq_ctx->data
 */
    (* ieee8021BridgeBasePortDelayExceededDiscards_val_ptr ).high = rowreq_ctx->data.ieee8021BridgeBasePortDelayExceededDiscards.high;
    (* ieee8021BridgeBasePortDelayExceededDiscards_val_ptr ).low = rowreq_ctx->data.ieee8021BridgeBasePortDelayExceededDiscards.low;


    return MFD_SUCCESS;
} /* ieee8021BridgeBasePortDelayExceededDiscards_get */

/*---------------------------------------------------------------------
 * IEEE8021-BRIDGE-MIB::ieee8021BridgeBasePortEntry.ieee8021BridgeBasePortMtuExceededDiscards
 * ieee8021BridgeBasePortMtuExceededDiscards is subid 5 of ieee8021BridgeBasePortEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.111.2.802.1.1.2.1.1.4.1.5
 * Description:
The number of frames discarded by this port due
        to an excessive size.  It is incremented by both
        transparent and source route bridges.

        Discontinuities in the value of the counter can occur
        at re-initialization of the management system, and at
        other times as indicated by the value of
        ifCounterDiscontinuityTime object of the associated
        interface (if any).
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is COUNTER64 (based on perltype COUNTER64)
 * The net-snmp type is ASN_COUNTER64. The C type decl is U64 (U64)
 */
/**
 * Extract the current value of the ieee8021BridgeBasePortMtuExceededDiscards data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param ieee8021BridgeBasePortMtuExceededDiscards_val_ptr
 *        Pointer to storage for a U64 variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
ieee8021BridgeBasePortMtuExceededDiscards_get( ieee8021BridgeBasePortTable_rowreq_ctx *rowreq_ctx, U64 * ieee8021BridgeBasePortMtuExceededDiscards_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != ieee8021BridgeBasePortMtuExceededDiscards_val_ptr );

/*
 * TODO:231:o: |-> copy ieee8021BridgeBasePortMtuExceededDiscards data.
 * get (* ieee8021BridgeBasePortMtuExceededDiscards_val_ptr ).low and (* ieee8021BridgeBasePortMtuExceededDiscards_val_ptr ).high from rowreq_ctx->data
 */
    (* ieee8021BridgeBasePortMtuExceededDiscards_val_ptr ).high = rowreq_ctx->data.ieee8021BridgeBasePortMtuExceededDiscards.high;
    (* ieee8021BridgeBasePortMtuExceededDiscards_val_ptr ).low = rowreq_ctx->data.ieee8021BridgeBasePortMtuExceededDiscards.low;


    return MFD_SUCCESS;
} /* ieee8021BridgeBasePortMtuExceededDiscards_get */

/*---------------------------------------------------------------------
 * IEEE8021-BRIDGE-MIB::ieee8021BridgeBasePortEntry.ieee8021BridgeBasePortCapabilities
 * ieee8021BridgeBasePortCapabilities is subid 6 of ieee8021BridgeBasePortEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.111.2.802.1.1.2.1.1.4.1.6
 * Description:
Indicates the parts of IEEE 802.1D and 802.1Q that are
        optional on a per-port basis, that are implemented by
        this device, and that are manageable through this MIB.

        dot1qDot1qTagging(0), -- supports 802.1Q VLAN tagging of
                              -- frames and MVRP.
        dot1qConfigurableAcceptableFrameTypes(1),
                              -- allows modified values of
                              -- dot1qPortAcceptableFrameTypes.
        dot1qIngressFiltering(2)
                              -- supports the discarding of any
                              -- frame received on a Port whose
                              -- VLAN classification does not
                              -- include that Port in its Member
                              -- set.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  1      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 * Enum range: 3/8. Values:  dot1qDot1qTagging(0), dot1qConfigurableAcceptableFrameTypes(1), dot1qIngressFiltering(2)
 *
 * Its syntax is BITS (based on perltype BITS)
 * The net-snmp type is ASN_OCTET_STR. The C type decl is char (u_long)
 * This data type requires a length.
 */
/**
 * Extract the current value of the ieee8021BridgeBasePortCapabilities data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param ieee8021BridgeBasePortCapabilities_val_ptr
 *        Pointer to storage for a char variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
ieee8021BridgeBasePortCapabilities_get( ieee8021BridgeBasePortTable_rowreq_ctx *rowreq_ctx, u_long * ieee8021BridgeBasePortCapabilities_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != ieee8021BridgeBasePortCapabilities_val_ptr );


    DEBUGMSGTL(("verbose:ieee8021BridgeBasePortTable:ieee8021BridgeBasePortCapabilities_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the ieee8021BridgeBasePortCapabilities data.
 * copy (* ieee8021BridgeBasePortCapabilities_val_ptr ) from rowreq_ctx->data
 */
    /*
     * TODO:242:o: update or replace BITS tests (get).
     * If ieee8021BridgeBasePortCapabilities data is stored in SNMP BIT order, individual
     * bit tests are redundant, and you can do a straight copy. If not, then
     * update each if condition to test the correct bit.
     *
     * NOTE WELL: setting bit '0' for:
     *             C  0x0000001
     *          SNMP  0x8000000
     *
     * assuming generated code keeps ieee8021BridgeBasePortCapabilities BITS in SNMP order.
     */
    (* ieee8021BridgeBasePortCapabilities_val_ptr ) =
        rowreq_ctx->data.ieee8021BridgeBasePortCapabilities;

    return MFD_SUCCESS;
} /* ieee8021BridgeBasePortCapabilities_get */

/*---------------------------------------------------------------------
 * IEEE8021-BRIDGE-MIB::ieee8021BridgeBasePortEntry.ieee8021BridgeBasePortTypeCapabilities
 * ieee8021BridgeBasePortTypeCapabilities is subid 7 of ieee8021BridgeBasePortEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.111.2.802.1.1.2.1.1.4.1.7
 * Description:
Indicates the capabilities of this port.  The corresponding
         instance of ieee8021BridgeBasePortType can potentially take
         any of the values for which the corresponding bit in this
         object is 1.  The possible port types are as follows:

             customerVlanPort(0) - Indicates the port can be a C-tag
                 aware port of an enterprise VLAN aware bridge.

             providerNetworkPort(1) - Indicates the port can be an
                 S-tag aware port of a Provider Bridge or Backbone
                 Edge Bridge used for connections within a PBN or
                 PBBN.

             customerNetworkPort(2) - Indicates the port can be an
                 S-tag aware port of a Provider Bridge or Backbone
                 Edge Bridge used for connections to the exterior of
                 a PBN or PBBN.

             customerEdgePort(3) - Indicates the port can be a C-tag
                 aware port of a Provider Bridge used for connections
                 to the exterior of a PBN or PBBN.

             customerBackbonePort(4) - Indicates the port can be a
                 I-tag aware port of a Backbone Edge Bridge's
                 B-component.

             virtualInstancePort(5) - Indicates the port can be a
                 virtual S-tag aware port within a Backbone Edge
                 Bridge's I-component which is responsible for
                 handling S-tagged traffic for a specific backbone
                 service instance.

             dBridgePort(6) - Indicates the port can be a VLAN-unaware
                 member of an 802.1D bridge.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  1      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 * Enum range: 5/8. Values:  customerVlanPort(0), providerNetworkPort(1), customerNetworkPort(2), customerEdgePort(3), customerBackbonePort(4), virtualInstancePort(5), dBridgePort(6)
 *
 * Its syntax is BITS (based on perltype BITS)
 * The net-snmp type is ASN_OCTET_STR. The C type decl is char (u_long)
 * This data type requires a length.
 */
/**
 * Extract the current value of the ieee8021BridgeBasePortTypeCapabilities data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param ieee8021BridgeBasePortTypeCapabilities_val_ptr
 *        Pointer to storage for a char variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
ieee8021BridgeBasePortTypeCapabilities_get( ieee8021BridgeBasePortTable_rowreq_ctx *rowreq_ctx, u_long * ieee8021BridgeBasePortTypeCapabilities_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != ieee8021BridgeBasePortTypeCapabilities_val_ptr );


    DEBUGMSGTL(("verbose:ieee8021BridgeBasePortTable:ieee8021BridgeBasePortTypeCapabilities_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the ieee8021BridgeBasePortTypeCapabilities data.
 * copy (* ieee8021BridgeBasePortTypeCapabilities_val_ptr ) from rowreq_ctx->data
 */
    /*
     * TODO:242:o: update or replace BITS tests (get).
     * If ieee8021BridgeBasePortTypeCapabilities data is stored in SNMP BIT order, individual
     * bit tests are redundant, and you can do a straight copy. If not, then
     * update each if condition to test the correct bit.
     *
     * NOTE WELL: setting bit '0' for:
     *             C  0x0000001
     *          SNMP  0x8000000
     *
     * assuming generated code keeps ieee8021BridgeBasePortTypeCapabilities BITS in SNMP order.
     */
    (* ieee8021BridgeBasePortTypeCapabilities_val_ptr ) =
        rowreq_ctx->data.ieee8021BridgeBasePortTypeCapabilities;

    return MFD_SUCCESS;
} /* ieee8021BridgeBasePortTypeCapabilities_get */

/*---------------------------------------------------------------------
 * IEEE8021-BRIDGE-MIB::ieee8021BridgeBasePortEntry.ieee8021BridgeBasePortType
 * ieee8021BridgeBasePortType is subid 8 of ieee8021BridgeBasePortEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.111.2.802.1.1.2.1.1.4.1.8
 * Description:
The port type.  This value must be persistent over power up
         restart/reboot.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  1      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 * Enum range: 7/16. Values:  none(1), customerVlanPort(2), providerNetworkPort(3), customerNetworkPort(4), customerEdgePort(5), customerBackbonePort(6), virtualInstancePort(7), dBridgePort(8)
 *
 * Its syntax is IEEE8021BridgePortType (based on perltype INTEGER)
 * The net-snmp type is ASN_INTEGER. The C type decl is long (u_long)
 */
/**
 * Extract the current value of the ieee8021BridgeBasePortType data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param ieee8021BridgeBasePortType_val_ptr
 *        Pointer to storage for a long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
ieee8021BridgeBasePortType_get( ieee8021BridgeBasePortTable_rowreq_ctx *rowreq_ctx, u_long * ieee8021BridgeBasePortType_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != ieee8021BridgeBasePortType_val_ptr );


    DEBUGMSGTL(("verbose:ieee8021BridgeBasePortTable:ieee8021BridgeBasePortType_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the ieee8021BridgeBasePortType data.
 * copy (* ieee8021BridgeBasePortType_val_ptr ) from rowreq_ctx->data
 */
    (* ieee8021BridgeBasePortType_val_ptr ) = rowreq_ctx->data.ieee8021BridgeBasePortType;

    return MFD_SUCCESS;
} /* ieee8021BridgeBasePortType_get */

/*---------------------------------------------------------------------
 * IEEE8021-BRIDGE-MIB::ieee8021BridgeBasePortEntry.ieee8021BridgeBasePortExternal
 * ieee8021BridgeBasePortExternal is subid 9 of ieee8021BridgeBasePortEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.111.2.802.1.1.2.1.1.4.1.9
 * Description:
A boolean indicating whether the port is external.  A value of
        true(1) means the port is external.  A value of false(2) means
        the port is internal.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  1      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 * Enum range: 2/8. Values:  true(1), false(2)
 *
 * Its syntax is TruthValue (based on perltype INTEGER)
 * The net-snmp type is ASN_INTEGER. The C type decl is long (u_long)
 */
/**
 * Extract the current value of the ieee8021BridgeBasePortExternal data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param ieee8021BridgeBasePortExternal_val_ptr
 *        Pointer to storage for a long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
ieee8021BridgeBasePortExternal_get( ieee8021BridgeBasePortTable_rowreq_ctx *rowreq_ctx, u_long * ieee8021BridgeBasePortExternal_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != ieee8021BridgeBasePortExternal_val_ptr );


    DEBUGMSGTL(("verbose:ieee8021BridgeBasePortTable:ieee8021BridgeBasePortExternal_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the ieee8021BridgeBasePortExternal data.
 * copy (* ieee8021BridgeBasePortExternal_val_ptr ) from rowreq_ctx->data
 */
    (* ieee8021BridgeBasePortExternal_val_ptr ) = rowreq_ctx->data.ieee8021BridgeBasePortExternal;

    return MFD_SUCCESS;
} /* ieee8021BridgeBasePortExternal_get */

/*---------------------------------------------------------------------
 * IEEE8021-BRIDGE-MIB::ieee8021BridgeBasePortEntry.ieee8021BridgeBasePortAdminPointToPoint
 * ieee8021BridgeBasePortAdminPointToPoint is subid 10 of ieee8021BridgeBasePortEntry.
 * Its status is Current, and its access level is ReadWrite.
 * OID: .1.3.111.2.802.1.1.2.1.1.4.1.10
 * Description:
For a port running spanning tree, this object represents the
         administrative point-to-point status of the LAN segment
         attached to this port, using the enumeration values of
         6.4.3.  A value of forceTrue(1) indicates
         that this port should always be treated as if it is
         connected to a point-to-point link.  A value of
         forceFalse(2) indicates that this port should be treated as
         having a shared media connection.  A value of auto(3)
         indicates that this port is considered to have a
         point-to-point link if it is an Aggregator and all of its
         members are aggregatable, or if the MAC entity
         is configured for full duplex operation, either through
         auto-negotiation or by management means.  Manipulating this
         object changes the underlying adminPointToPointMAC.

         For a VIP, the adminPointToPointMAC parameter controls
         the mechanism by which the Default Backbone Destination
         parameter for the VIP is determined.  For a backbone
         service instance that includes only 2 VIPs, the value
         may be set to forceTrue(1) which permits dynamic learning
         of the Default Backbone Destination parameter.  For a
         backbone service instance that includes more than 2 VIPs,
         the value must be set to ForceFalse(2) or auto(3).

         When this object is set to forceTrue(1) for a VIP, the
         Default Backbone Destination parameter is modified by
         the subsequent M_UNITDATA.indications as specified in
         6.10.1 (and described in 26.4.1).  Whenever the parameter
         is set to ForceFalse(2) or auto(3), the value for the
         Default Backbone Destination parameter is set to the
         Backbone Service Instance Group Address for the VIP-ISID.

         The value of this object MUST be retained across
         reinitializations of the management system.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  1      hasdefval 1
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   1
 *   defval: forceFalse
 *
 * Enum range: 3/8. Values:  forceTrue(1), forceFalse(2), auto(3)
 *
 * Its syntax is INTEGER (based on perltype INTEGER)
 * The net-snmp type is ASN_INTEGER. The C type decl is long (u_long)
 */
/**
 * Extract the current value of the ieee8021BridgeBasePortAdminPointToPoint data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param ieee8021BridgeBasePortAdminPointToPoint_val_ptr
 *        Pointer to storage for a long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
ieee8021BridgeBasePortAdminPointToPoint_get( ieee8021BridgeBasePortTable_rowreq_ctx *rowreq_ctx, u_long * ieee8021BridgeBasePortAdminPointToPoint_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != ieee8021BridgeBasePortAdminPointToPoint_val_ptr );


    DEBUGMSGTL(("verbose:ieee8021BridgeBasePortTable:ieee8021BridgeBasePortAdminPointToPoint_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the ieee8021BridgeBasePortAdminPointToPoint data.
 * copy (* ieee8021BridgeBasePortAdminPointToPoint_val_ptr ) from rowreq_ctx->data
 */
    (* ieee8021BridgeBasePortAdminPointToPoint_val_ptr ) = rowreq_ctx->data.ieee8021BridgeBasePortAdminPointToPoint;

    return MFD_SUCCESS;
} /* ieee8021BridgeBasePortAdminPointToPoint_get */

/*---------------------------------------------------------------------
 * IEEE8021-BRIDGE-MIB::ieee8021BridgeBasePortEntry.ieee8021BridgeBasePortOperPointToPoint
 * ieee8021BridgeBasePortOperPointToPoint is subid 11 of ieee8021BridgeBasePortEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.111.2.802.1.1.2.1.1.4.1.11
 * Description:
For a port running spanning tree, this object represents
         the operational point-to-point status of the LAN segment
         attached to this port.  It indicates whether a port is
         considered to have a point-to-point connection.
         If adminPointToPointMAC is set to auto(2), then the value
         of operPointToPointMAC is determined in accordance with the
         specific procedures defined for the MAC entity concerned,
         as defined in 6.5 of IEEE 802.1w.  The value is
         determined dynamically; that is, it is re-evaluated whenever
         the value of adminPointToPointMAC changes, and whenever
         the specific procedures defined for the MAC entity evaluate
         a change in its point-to-point status.

         For a VIP, this object simply reflects the value of the
         corresponding instance of ieee8021BridgeBasePortAdminPointToPoint.
         The value will be true(1) if that object is forceTrue(1), and
         the value will be false(2) if the value of that object is either
         forceFalse(2) or auto(3).
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  1      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 * Enum range: 2/8. Values:  true(1), false(2)
 *
 * Its syntax is TruthValue (based on perltype INTEGER)
 * The net-snmp type is ASN_INTEGER. The C type decl is long (u_long)
 */
/**
 * Extract the current value of the ieee8021BridgeBasePortOperPointToPoint data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param ieee8021BridgeBasePortOperPointToPoint_val_ptr
 *        Pointer to storage for a long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int
ieee8021BridgeBasePortOperPointToPoint_get( ieee8021BridgeBasePortTable_rowreq_ctx *rowreq_ctx, u_long * ieee8021BridgeBasePortOperPointToPoint_val_ptr )
{
   /** we should have a non-NULL pointer */
   netsnmp_assert( NULL != ieee8021BridgeBasePortOperPointToPoint_val_ptr );


    DEBUGMSGTL(("verbose:ieee8021BridgeBasePortTable:ieee8021BridgeBasePortOperPointToPoint_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the ieee8021BridgeBasePortOperPointToPoint data.
 * copy (* ieee8021BridgeBasePortOperPointToPoint_val_ptr ) from rowreq_ctx->data
 */
    (* ieee8021BridgeBasePortOperPointToPoint_val_ptr ) = rowreq_ctx->data.ieee8021BridgeBasePortOperPointToPoint;

    return MFD_SUCCESS;
} /* ieee8021BridgeBasePortOperPointToPoint_get */

/*---------------------------------------------------------------------
 * IEEE8021-BRIDGE-MIB::ieee8021BridgeBasePortEntry.ieee8021BridgeBasePortName
 * ieee8021BridgeBasePortName is subid 12 of ieee8021BridgeBasePortEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.111.2.802.1.1.2.1.1.4.1.12
 * Description:
A text string of up to 32 characters, of locally determined significance.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 1      hashint   1
 *   settable   0
 *   hint: 255t
 *
 * Ranges:  0 - 255;
 *
 * Its syntax is SnmpAdminString (based on perltype OCTETSTR)
 * The net-snmp type is ASN_OCTET_STR. The C type decl is char (char)
 * This data type requires a length.  (Max 255)
 */
/**
 * Extract the current value of the ieee8021BridgeBasePortName data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param ieee8021BridgeBasePortName_val_ptr_ptr
 *        Pointer to storage for a char variable
 * @param ieee8021BridgeBasePortName_val_ptr_len_ptr
 *        Pointer to a size_t. On entry, it will contain the size (in bytes)
 *        pointed to by ieee8021BridgeBasePortName.
 *        On exit, this value should contain the data size (in bytes).
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
*
 * @note If you need more than (*ieee8021BridgeBasePortName_val_ptr_len_ptr) bytes of memory,
 *       allocate it using malloc() and update ieee8021BridgeBasePortName_val_ptr_ptr.
 *       <b>DO NOT</b> free the previous pointer.
 *       The MFD helper will release the memory you allocate.
 *
 * @remark If you call this function yourself, you are responsible
 *         for checking if the pointer changed, and freeing any
 *         previously allocated memory. (Not necessary if you pass
 *         in a pointer to static memory, obviously.)
 */
int
ieee8021BridgeBasePortName_get( ieee8021BridgeBasePortTable_rowreq_ctx *rowreq_ctx, char **ieee8021BridgeBasePortName_val_ptr_ptr, size_t *ieee8021BridgeBasePortName_val_ptr_len_ptr )
{
   /** we should have a non-NULL pointer and enough storage */
   netsnmp_assert( (NULL != ieee8021BridgeBasePortName_val_ptr_ptr) && (NULL != *ieee8021BridgeBasePortName_val_ptr_ptr));
   netsnmp_assert( NULL != ieee8021BridgeBasePortName_val_ptr_len_ptr );


    DEBUGMSGTL(("verbose:ieee8021BridgeBasePortTable:ieee8021BridgeBasePortName_get","called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:231:o: |-> Extract the current value of the ieee8021BridgeBasePortName data.
 * copy (* ieee8021BridgeBasePortName_val_ptr_ptr ) data and (* ieee8021BridgeBasePortName_val_ptr_len_ptr ) from rowreq_ctx->data
 */
    /*
     * make sure there is enough space for ieee8021BridgeBasePortName data
     */
    if ((NULL == (* ieee8021BridgeBasePortName_val_ptr_ptr )) ||
        ((* ieee8021BridgeBasePortName_val_ptr_len_ptr ) <
         (rowreq_ctx->data.ieee8021BridgeBasePortName_len* sizeof(rowreq_ctx->data.ieee8021BridgeBasePortName[0])))) {
        /*
         * allocate space for ieee8021BridgeBasePortName data
         */
        (* ieee8021BridgeBasePortName_val_ptr_ptr ) = malloc(rowreq_ctx->data.ieee8021BridgeBasePortName_len* sizeof(rowreq_ctx->data.ieee8021BridgeBasePortName[0]));
        if(NULL == (* ieee8021BridgeBasePortName_val_ptr_ptr )) {
            snmp_log(LOG_ERR,"could not allocate memory\n");
            return MFD_ERROR;
        }
    }
    (* ieee8021BridgeBasePortName_val_ptr_len_ptr ) = rowreq_ctx->data.ieee8021BridgeBasePortName_len* sizeof(rowreq_ctx->data.ieee8021BridgeBasePortName[0]);
    memcpy( (* ieee8021BridgeBasePortName_val_ptr_ptr ), rowreq_ctx->data.ieee8021BridgeBasePortName, rowreq_ctx->data.ieee8021BridgeBasePortName_len* sizeof(rowreq_ctx->data.ieee8021BridgeBasePortName[0]) );

    return MFD_SUCCESS;
} /* ieee8021BridgeBasePortName_get */



/** @} */
