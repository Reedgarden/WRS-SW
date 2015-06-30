/*
  Register definitions for slave core: WR Watchdog module

  * File           : wdog-regs.h
  * Author         : auto-generated by wbgen2 from wdog-regs.wb
  * Standard       : ANSI C

    THIS FILE WAS GENERATED BY wbgen2 FROM SOURCE FILE wdog-regs.wb
    DO NOT HAND-EDIT UNLESS IT'S ABSOLUTELY NECESSARY!

*/

#ifndef __WBGEN2_REGDEFS_WDOG
#define __WBGEN2_REGDEFS_WDOG

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#endif


#if defined( __GNUC__)
#define PACKED __attribute__ ((packed))
#else
#error "Unsupported compiler?"
#endif

#ifndef __WBGEN2_MACROS_DEFINED__
#define __WBGEN2_MACROS_DEFINED__
#define WBGEN2_GEN_MASK(offset, size) (((1<<(size))-1) << (offset))
#define WBGEN2_GEN_WRITE(value, offset, size) (((value) & ((1<<(size))-1)) << (offset))
#define WBGEN2_GEN_READ(reg, offset, size) (((reg) >> (offset)) & ((1<<(size))-1))
#define WBGEN2_SIGN_EXTEND(value, bits) (((value) & (1<<bits) ? ~((1<<(bits))-1): 0 ) | (value))
#endif


/* definitions for register: Restart counter */

/* definitions for register: Control Register */

/* definitions for field: Port select in reg: Control Register */
#define WDOG_CR_PORT_MASK                     WBGEN2_GEN_MASK(0, 8)
#define WDOG_CR_PORT_SHIFT                    0
#define WDOG_CR_PORT_W(value)                 WBGEN2_GEN_WRITE(value, 0, 8)
#define WDOG_CR_PORT_R(reg)                   WBGEN2_GEN_READ(reg, 0, 8)

/* definitions for field: Force reset in reg: Control Register */
#define WDOG_CR_RST                           WBGEN2_GEN_MASK(31, 1)

/* definitions for register: Port FSM activity register */

/* definitions for register: Port FSM register */

/* definitions for field: IB alloc FSM state in reg: Port FSM register */
#define WDOG_FSM_IB_ALLOC_MASK                WBGEN2_GEN_MASK(0, 4)
#define WDOG_FSM_IB_ALLOC_SHIFT               0
#define WDOG_FSM_IB_ALLOC_W(value)            WBGEN2_GEN_WRITE(value, 0, 4)
#define WDOG_FSM_IB_ALLOC_R(reg)              WBGEN2_GEN_READ(reg, 0, 4)

/* definitions for field: IB transfer FSM state in reg: Port FSM register */
#define WDOG_FSM_IB_TRANS_MASK                WBGEN2_GEN_MASK(4, 4)
#define WDOG_FSM_IB_TRANS_SHIFT               4
#define WDOG_FSM_IB_TRANS_W(value)            WBGEN2_GEN_WRITE(value, 4, 4)
#define WDOG_FSM_IB_TRANS_R(reg)              WBGEN2_GEN_READ(reg, 4, 4)

/* definitions for field: IB receive FSM state in reg: Port FSM register */
#define WDOG_FSM_IB_RCV_MASK                  WBGEN2_GEN_MASK(8, 4)
#define WDOG_FSM_IB_RCV_SHIFT                 8
#define WDOG_FSM_IB_RCV_W(value)              WBGEN2_GEN_WRITE(value, 8, 4)
#define WDOG_FSM_IB_RCV_R(reg)                WBGEN2_GEN_READ(reg, 8, 4)

/* definitions for field: IB LL FSM state in reg: Port FSM register */
#define WDOG_FSM_IB_LL_MASK                   WBGEN2_GEN_MASK(12, 4)
#define WDOG_FSM_IB_LL_SHIFT                  12
#define WDOG_FSM_IB_LL_W(value)               WBGEN2_GEN_WRITE(value, 12, 4)
#define WDOG_FSM_IB_LL_R(reg)                 WBGEN2_GEN_READ(reg, 12, 4)

/* definitions for field: OB prepare FSM state in reg: Port FSM register */
#define WDOG_FSM_OB_PREP_MASK                 WBGEN2_GEN_MASK(16, 4)
#define WDOG_FSM_OB_PREP_SHIFT                16
#define WDOG_FSM_OB_PREP_W(value)             WBGEN2_GEN_WRITE(value, 16, 4)
#define WDOG_FSM_OB_PREP_R(reg)               WBGEN2_GEN_READ(reg, 16, 4)

/* definitions for field: OB send FSM state in reg: Port FSM register */
#define WDOG_FSM_OB_SEND_MASK                 WBGEN2_GEN_MASK(20, 4)
#define WDOG_FSM_OB_SEND_SHIFT                20
#define WDOG_FSM_OB_SEND_W(value)             WBGEN2_GEN_WRITE(value, 20, 4)
#define WDOG_FSM_OB_SEND_R(reg)               WBGEN2_GEN_READ(reg, 20, 4)

/* definitions for field: FREE FSM state in reg: Port FSM register */
#define WDOG_FSM_FREE_MASK                    WBGEN2_GEN_MASK(24, 4)
#define WDOG_FSM_FREE_SHIFT                   24
#define WDOG_FSM_FREE_W(value)                WBGEN2_GEN_WRITE(value, 24, 4)
#define WDOG_FSM_FREE_R(reg)                  WBGEN2_GEN_READ(reg, 24, 4)

PACKED struct WDOG_WB {
  /* [0x0]: REG Restart counter */
  uint32_t RST_CNT;
  /* [0x4]: REG Control Register */
  uint32_t CR;
  /* [0x8]: REG Port FSM activity register */
  uint32_t ACT;
  /* [0xc]: REG Port FSM register */
  uint32_t FSM;
};

#endif
