/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 14170 $ of $
 *
 * $Id:$
 */
#ifndef PSTATSTABLE_DATA_ACCESS_H
#define PSTATSTABLE_DATA_ACCESS_H

#ifdef __cplusplus
extern          "C" {
#endif


    /*
     *********************************************************************
     * function declarations
     */

    /*
     *********************************************************************
     * Table declarations
     */
/**********************************************************************
 **********************************************************************
 ***
 *** Table pstatsTable
 ***
 **********************************************************************
 **********************************************************************/
    /*
     * WR-SWITCH-MIB::pstatsTable is subid 2 of wrsPstats.
     * Its status is Current.
     * OID: .1.3.6.1.4.1.96.100.2.2, length: 10
     */


    int             pstatsTable_init_data(pstatsTable_registration *
                                          pstatsTable_reg);


    /*
     * TODO:180:o: Review pstatsTable cache timeout.
     * The number of seconds before the cache times out
     */
#define PSTATSTABLE_CACHE_TIMEOUT   60

    void            pstatsTable_container_init(netsnmp_container **
                                               container_ptr_ptr,
                                               netsnmp_cache * cache);
    void            pstatsTable_container_shutdown(netsnmp_container *
                                                   container_ptr);

    int             pstatsTable_container_load(netsnmp_container *
                                               container);
    void            pstatsTable_container_free(netsnmp_container *
                                               container);

    int             pstatsTable_cache_load(netsnmp_container * container);
    void            pstatsTable_cache_free(netsnmp_container * container);

    /*
     ***************************************************
     ***             START EXAMPLE CODE              ***
     ***---------------------------------------------***/
    /*
     *********************************************************************
     * Since we have no idea how you really access your data, we'll go with
     * a worst case example: a flat text file.
     */
#define MAX_LINE_SIZE 256
    /*
     ***---------------------------------------------***
     ***              END  EXAMPLE CODE              ***
     ***************************************************/
    int             pstatsTable_row_prep(pstatsTable_rowreq_ctx *
                                         rowreq_ctx);



#ifdef __cplusplus
}
#endif
#endif                          /* PSTATSTABLE_DATA_ACCESS_H */
