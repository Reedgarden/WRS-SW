/*
 * Note: this file originally auto-generated by mib2c using
 *  : mib2c.raw-table.conf 17436 2009-03-31 15:12:19Z dts12 $
 */
#ifndef IEEE8021QBRIDGETPFDBTABLE_H
#define IEEE8021QBRIDGETPFDBTABLE_H

enum fdb_entry_status {
    other           = 1,
    Invalid         = 2,
    Learned         = 3,
    Self            = 4,
    Mgmt            = 5
};

void init_ieee8021QBridgeTpFdbTable(void);

#endif /* IEEE8021QBRIDGETPFDBTABLE_H */
