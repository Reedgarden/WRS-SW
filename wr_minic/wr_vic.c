/*
 * VIC controller, as implemented in FPGA in the White Rabbit switch
 *
 * Copyright (c) 2009, 2010 CERN
 * Author: Tomasz Wlostowski <tomasz.wlostowski@cern.ch>
 * Author: Alessandro Rubini <rubini@gnudd.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>

#include <asm/irq.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>

#define DRV_MODULE_VERSION "0.2"
#define DRV_NAME "wr_vic"
#define PFX DRV_NAME ": "

#define WRVIC_NR_IRQS 32 /* We have 32 possible interrupt sources */

/* The following stanza comes from <mach/irq.h>: */
     /*
      * IRQ interrupt symbols are the AT91xxx_ID_* symbols
      * for IRQs handled directly through the AIC, or else the AT91_PIN_*
      * symbols in gpio.h for ones handled indirectly as GPIOs.
      * We make provision for 5 banks of GPIO.
     #define NR_IRQS         (NR_AIC_IRQS + (5 * 32))
      */
/* Therefore, we must have a bigger NR_IRQS and can't work otherwise */
#if NR_IRQS < (NR_AIC_IRQS + (5 * 32) + WRVIC_NR_IRQS)
#error "Please fix the kernel to allow for WR-VIC interrupts"
#endif

#define WRVIC_BASE_IRQ (NR_AIC_IRQS + (5 * 32)) /* top of GPIO interrupts */

/*
 * What follows is header-like material, but we need no header for
 * external modules. Thus all defines are kept here to avoid confusion.
 */
#define FPGA_BASE_WRVIC	0x70030000
#define FPGA_SIZE_WRVIC	0x00001000

struct wrvic_regs {
	u32 reg_ctl;	/* [0x00]: WRVIC Control Register */
	u32 reg_risr;	/* [0x04]: Raw Interrupt Status Register */
	u32 reg_ier;	/* [0x08]: Interrupt Enable Register */
	u32 reg_idr;	/* [0x0c]: Interrupt Disable Register */
	u32 reg_imr;	/* [0x10]: Interrupt Mask Register */
	u32 reg_var;	/* [0x14]: Vector Address Register */
	u32 unused0;
	u32 reg_eoir;	/* [0x1c]: End Of Irq Ack Register */
	u32 unused1[((0x80-0x20)/4)];
	u32 vector[WRVIC_NR_IRQS];
};

static struct wrvic_regs __iomem *wrvic_regs;

#define WRVIC_CTL_ENABLE                        (1<<0)
#define WRVIC_CTL_POL                           (1<<1)

#define WRVIC_SPURIOUS_IRQ 0x12345678 /* A diagnostic help */

#define wrvic_readl(r)		__raw_readl(&wrvic_regs->r);
#define wrvic_writel(val, r)	__raw_writel(val, &wrvic_regs->r);

/* We only have two methods: unmask (enable) and mask (disable) */
static void wrvic_unmask_irq(unsigned int irq)
{
	irq -= WRVIC_BASE_IRQ;
	wrvic_writel(irq, vector[irq]);
	wrvic_writel(1 << irq, reg_ier);
}

static void wrvic_mask_irq(unsigned int irq)
{
	irq -= WRVIC_BASE_IRQ;
	wrvic_writel( 1 << irq, reg_idr);
	wrvic_writel(WRVIC_SPURIOUS_IRQ, vector[irq]);
}

static struct irq_chip wrvic_irqchip = {
	.name		= "WR-VIC",
	.mask		= wrvic_mask_irq,
	.unmask		= wrvic_unmask_irq,
};

static void wrvic_handler(unsigned int irq, struct irq_desc *desc)
{
	u32 pending = wrvic_readl(reg_var);

	if (pending == WRVIC_SPURIOUS_IRQ) {
		printk(KERN_ERR PFX "spurious interrupt\n");
		wrvic_writel(0, reg_eoir); /* clear pending flag */
		return;
	}

	generic_handle_irq(WRVIC_BASE_IRQ + pending);
	wrvic_writel(0, reg_eoir); /* clear pending flag */
}

int __init wrvic_init(void)
{
	int i;

	wrvic_regs = ioremap(FPGA_BASE_WRVIC, FPGA_SIZE_WRVIC);
	if (!wrvic_regs)
		return -ENOMEM;

	/* First, prime the WRVIC with "invalid" vectors and disable all irq */
	for (i = 0; i < WRVIC_NR_IRQS; i++)
		wrvic_writel(WRVIC_SPURIOUS_IRQ, vector[i]);
	wrvic_writel(~0, reg_idr);

	for(i = WRVIC_BASE_IRQ; i <= WRVIC_BASE_IRQ + WRVIC_NR_IRQS; i++) {
		set_irq_chip(i, &wrvic_irqchip);
		set_irq_handler(i, handle_level_irq);
		set_irq_flags(i, IRQF_VALID | IRQF_PROBE);
	}
	set_irq_chained_handler(AT91SAM9263_ID_IRQ0, wrvic_handler);
	set_irq_type(AT91SAM9263_ID_IRQ0, IRQF_TRIGGER_LOW);

	/* Enable. "CTL_POL" is 0 which means active low (falling) */
	wrvic_writel(WRVIC_CTL_ENABLE, reg_ctl);

	return 0;
}

module_init(wrvic_init);
/* no exit is expected */

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("White Rabbit Vectored Interrupt Controller");
MODULE_VERSION(DRV_MODULE_VERSION);
