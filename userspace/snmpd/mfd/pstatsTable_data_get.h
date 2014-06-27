/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 12088 $ of $
 *
 * $Id:$
 *
 * @file pstatsTable_data_get.h
 *
 * @addtogroup get
 *
 * Prototypes for get functions
 *
 * @{
 */
#ifndef PSTATSTABLE_DATA_GET_H
#define PSTATSTABLE_DATA_GET_H

#ifdef __cplusplus
extern          "C" {
#endif

    /*
     *********************************************************************
     * GET function declarations
     */

    /*
     *********************************************************************
     * GET Table declarations
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
    /*
     * indexes
     */

    int             pstatsDescr_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                    char **pstatsDescr_val_ptr_ptr,
                                    size_t *pstatsDescr_val_ptr_len_ptr);
    int             pstatsWR0_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                  u_long * pstatsWR0_val_ptr);
    int             pstatsWR1_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                  u_long * pstatsWR1_val_ptr);
    int             pstatsWR2_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                  u_long * pstatsWR2_val_ptr);
    int             pstatsWR3_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                  u_long * pstatsWR3_val_ptr);
    int             pstatsWR4_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                  u_long * pstatsWR4_val_ptr);
    int             pstatsWR5_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                  u_long * pstatsWR5_val_ptr);
    int             pstatsWR6_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                  u_long * pstatsWR6_val_ptr);
    int             pstatsWR7_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                  u_long * pstatsWR7_val_ptr);
    int             pstatsWR8_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                  u_long * pstatsWR8_val_ptr);
    int             pstatsWR9_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                  u_long * pstatsWR9_val_ptr);
    int             pstatsWR10_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                   u_long * pstatsWR10_val_ptr);
    int             pstatsWR11_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                   u_long * pstatsWR11_val_ptr);
    int             pstatsWR12_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                   u_long * pstatsWR12_val_ptr);
    int             pstatsWR13_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                   u_long * pstatsWR13_val_ptr);
    int             pstatsWR14_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                   u_long * pstatsWR14_val_ptr);
    int             pstatsWR15_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                   u_long * pstatsWR15_val_ptr);
    int             pstatsWR16_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                   u_long * pstatsWR16_val_ptr);
    int             pstatsWR17_get(pstatsTable_rowreq_ctx * rowreq_ctx,
                                   u_long * pstatsWR17_val_ptr);


    int             pstatsTable_indexes_set_tbl_idx(pstatsTable_mib_index *
                                                    tbl_idx,
                                                    long pstatsIndex_val);
    int             pstatsTable_indexes_set(pstatsTable_rowreq_ctx *
                                            rowreq_ctx,
                                            long pstatsIndex_val);




#ifdef __cplusplus
}
#endif
#endif                          /* PSTATSTABLE_DATA_GET_H */
/** @} */
