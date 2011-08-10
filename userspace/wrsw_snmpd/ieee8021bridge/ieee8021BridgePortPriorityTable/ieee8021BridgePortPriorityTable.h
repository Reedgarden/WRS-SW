/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 17337 $ of $
 *
 * $Id:$
 */
#ifndef IEEE8021BRIDGEPORTPRIORITYTABLE_H
#define IEEE8021BRIDGEPORTPRIORITYTABLE_H

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup misc misc: Miscellaneous routines
 *
 * @{
 */
#include <net-snmp/library/asn1.h>

/* other required module components */
    /* *INDENT-OFF*  */
config_add_mib(IEEE8021-BRIDGE-MIB)
config_require(IEEE8021-BRIDGE-MIB/ieee8021BridgePortPriorityTable/ieee8021BridgePortPriorityTable_interface)
config_require(IEEE8021-BRIDGE-MIB/ieee8021BridgePortPriorityTable/ieee8021BridgePortPriorityTable_data_access)
config_require(IEEE8021-BRIDGE-MIB/ieee8021BridgePortPriorityTable/ieee8021BridgePortPriorityTable_data_get)
config_require(IEEE8021-BRIDGE-MIB/ieee8021BridgePortPriorityTable/ieee8021BridgePortPriorityTable_data_set)
    /* *INDENT-ON*  */

/* OID and column number definitions for ieee8021BridgePortPriorityTable */
#include "ieee8021BridgePortPriorityTable_oids.h"

/* enum definions */
#include "ieee8021BridgePortPriorityTable_enums.h"

/* *********************************************************************
 * function declarations
 */
void init_ieee8021BridgePortPriorityTable(void);
void shutdown_ieee8021BridgePortPriorityTable(void);

/* *********************************************************************
 * Table declarations
 */
/**********************************************************************
 **********************************************************************
 ***
 *** Table ieee8021BridgePortPriorityTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * IEEE8021-BRIDGE-MIB::ieee8021BridgePortPriorityTable is subid 1 of ieee8021BridgePriority.
 * Its status is Current.
 * OID: .1.3.111.2.802.1.1.2.1.3.1, length: 11
*/
/* *********************************************************************
 * When you register your mib, you get to provide a generic
 * pointer that will be passed back to you for most of the
 * functions calls.
 *
 * TODO:100:r: Review all context structures
 */
    /*
     * TODO:101:o: |-> Review ieee8021BridgePortPriorityTable registration context.
     */
typedef netsnmp_data_list ieee8021BridgePortPriorityTable_registration;

/**********************************************************************/
/*
 * TODO:110:r: |-> Review ieee8021BridgePortPriorityTable data context structure.
 * This structure is used to represent the data for ieee8021BridgePortPriorityTable.
 */
/*
 * This structure contains storage for all the columns defined in the
 * ieee8021BridgePortPriorityTable.
 */
typedef struct ieee8021BridgePortPriorityTable_data_s {
    
        /*
         * ieee8021BridgePortDefaultUserPriority(1)/IEEE8021PriorityValue/ASN_UNSIGNED/u_long(u_long)//l/A/W/e/R/d/H
         */
   u_long   ieee8021BridgePortDefaultUserPriority;
    
        /*
         * ieee8021BridgePortNumTrafficClasses(2)/INTEGER32/ASN_INTEGER/long(long)//l/A/W/e/R/d/h
         */
   long   ieee8021BridgePortNumTrafficClasses;
    
        /*
         * ieee8021BridgePortPriorityCodePointSelection(3)/IEEE8021PriorityCodePoint/ASN_INTEGER/long(u_long)//l/A/W/E/r/d/h
         */
   u_long   ieee8021BridgePortPriorityCodePointSelection;
    
        /*
         * ieee8021BridgePortUseDEI(4)/TruthValue/ASN_INTEGER/long(u_long)//l/A/W/E/r/d/h
         */
   u_long   ieee8021BridgePortUseDEI;
    
        /*
         * ieee8021BridgePortRequireDropEncoding(5)/TruthValue/ASN_INTEGER/long(u_long)//l/A/W/E/r/D/h
         */
   u_long   ieee8021BridgePortRequireDropEncoding;
    
        /*
         * ieee8021BridgePortServiceAccessPrioritySelection(6)/TruthValue/ASN_INTEGER/long(u_long)//l/A/W/E/r/d/h
         */
   u_long   ieee8021BridgePortServiceAccessPrioritySelection;
    
} ieee8021BridgePortPriorityTable_data;


/* *********************************************************************
 * TODO:115:o: |-> Review ieee8021BridgePortPriorityTable undo context.
 * We're just going to use the same data structure for our
 * undo_context. If you want to do something more efficent,
 * define your typedef here.
 */
typedef ieee8021BridgePortPriorityTable_data ieee8021BridgePortPriorityTable_undo_data;

/*
 * TODO:120:r: |-> Review ieee8021BridgePortPriorityTable mib index.
 * This structure is used to represent the index for ieee8021BridgePortPriorityTable.
 */
typedef struct ieee8021BridgePortPriorityTable_mib_index_s {

        /*
         * ieee8021BridgeBasePortComponentId(1)/IEEE8021PbbComponentIdentifier/ASN_UNSIGNED/u_long(u_long)//l/a/w/e/R/d/H
         */
   u_long   ieee8021BridgeBasePortComponentId;

        /*
         * ieee8021BridgeBasePort(2)/IEEE8021BridgePortNumber/ASN_UNSIGNED/u_long(u_long)//l/a/w/e/R/d/H
         */
   u_long   ieee8021BridgeBasePort;


} ieee8021BridgePortPriorityTable_mib_index;

    /*
     * TODO:121:r: |   |-> Review ieee8021BridgePortPriorityTable max index length.
     * If you KNOW that your indexes will never exceed a certain
     * length, update this macro to that length.
*/
#define MAX_ieee8021BridgePortPriorityTable_IDX_LEN     2


/* *********************************************************************
 * TODO:130:o: |-> Review ieee8021BridgePortPriorityTable Row request (rowreq) context.
 * When your functions are called, you will be passed a
 * ieee8021BridgePortPriorityTable_rowreq_ctx pointer.
 */
typedef struct ieee8021BridgePortPriorityTable_rowreq_ctx_s {

    /** this must be first for container compare to work */
    netsnmp_index        oid_idx;
    oid                  oid_tmp[MAX_ieee8021BridgePortPriorityTable_IDX_LEN];
    
    ieee8021BridgePortPriorityTable_mib_index        tbl_idx;
    
    ieee8021BridgePortPriorityTable_data              data;
    unsigned int                column_exists_flags; /* flags for existence */
    ieee8021BridgePortPriorityTable_undo_data       * undo;
    unsigned int                column_set_flags; /* flags for set columns */


    /*
     * flags per row. Currently, the first (lower) 8 bits are reserved
     * for the user. See mfd.h for other flags.
     */
    u_int                       rowreq_flags;

    /*
     * TODO:131:o: |   |-> Add useful data to ieee8021BridgePortPriorityTable rowreq context.
     */
    
    /*
     * storage for future expansion
     */
    netsnmp_data_list             *ieee8021BridgePortPriorityTable_data_list;

} ieee8021BridgePortPriorityTable_rowreq_ctx;

typedef struct ieee8021BridgePortPriorityTable_ref_rowreq_ctx_s {
    ieee8021BridgePortPriorityTable_rowreq_ctx *rowreq_ctx;
} ieee8021BridgePortPriorityTable_ref_rowreq_ctx;

/* *********************************************************************
 * function prototypes
 */
    int ieee8021BridgePortPriorityTable_pre_request(ieee8021BridgePortPriorityTable_registration * user_context);
    int ieee8021BridgePortPriorityTable_post_request(ieee8021BridgePortPriorityTable_registration * user_context,
        int rc);

    int ieee8021BridgePortPriorityTable_rowreq_ctx_init(ieee8021BridgePortPriorityTable_rowreq_ctx *rowreq_ctx,
                                   void *user_init_ctx);
    void ieee8021BridgePortPriorityTable_rowreq_ctx_cleanup(ieee8021BridgePortPriorityTable_rowreq_ctx *rowreq_ctx);

    int ieee8021BridgePortPriorityTable_check_dependencies(ieee8021BridgePortPriorityTable_rowreq_ctx * rowreq_ctx); 
    int ieee8021BridgePortPriorityTable_commit(ieee8021BridgePortPriorityTable_rowreq_ctx * rowreq_ctx);

    ieee8021BridgePortPriorityTable_rowreq_ctx *
                  ieee8021BridgePortPriorityTable_row_find_by_mib_index(ieee8021BridgePortPriorityTable_mib_index *mib_idx);

extern const oid ieee8021BridgePortPriorityTable_oid[];
extern const int ieee8021BridgePortPriorityTable_oid_size;


#include "ieee8021BridgePortPriorityTable_interface.h"
#include "ieee8021BridgePortPriorityTable_data_access.h"
#include "ieee8021BridgePortPriorityTable_data_get.h"
#include "ieee8021BridgePortPriorityTable_data_set.h"

/*
 * DUMMY markers, ignore
 *
 * TODO:099:x: *************************************************************
 * TODO:199:x: *************************************************************
 * TODO:299:x: *************************************************************
 * TODO:399:x: *************************************************************
 * TODO:499:x: *************************************************************
 */

#ifdef __cplusplus
}
#endif

#endif /* IEEE8021BRIDGEPORTPRIORITYTABLE_H */
/** @} */
