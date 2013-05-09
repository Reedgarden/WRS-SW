/*
  Register definitions for slave core: WR Switch Hardware Debugging Unit

  * File           : hwdu-regs.h
  * Author         : auto-generated by wbgen2 from hwdu-regs.wb
  * Standard       : ANSI C

    THIS FILE WAS GENERATED BY wbgen2 FROM SOURCE FILE hwdu-regs.wb
    DO NOT HAND-EDIT UNLESS IT'S ABSOLUTELY NECESSARY!

*/

#ifndef __WBGEN2_REGDEFS_HWDU
#define __WBGEN2_REGDEFS_HWDU

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


/* definitions for register: Control Register */

/* definitions for field: Address of the register in reg: Control Register */
#define HWDU_CR_ADR_MASK                      WBGEN2_GEN_MASK(0, 16)
#define HWDU_CR_ADR_SHIFT                     0
#define HWDU_CR_ADR_W(value)                  WBGEN2_GEN_WRITE(value, 0, 16)
#define HWDU_CR_ADR_R(reg)                    WBGEN2_GEN_READ(reg, 0, 16)

/* definitions for field: Read error in reg: Control Register */
#define HWDU_CR_RD_ERR                        WBGEN2_GEN_MASK(30, 1)

/* definitions for field: Read register value in reg: Control Register */
#define HWDU_CR_RD_EN                         WBGEN2_GEN_MASK(31, 1)

/* definitions for register: Value of the requested register */

PACKED struct HWDU_WB {
  /* [0x0]: REG Control Register */
  uint32_t CR;
  /* [0x4]: REG Value of the requested register */
  uint32_t REG_VAL;
};

#endif
