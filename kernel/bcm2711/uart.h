#include <stdtypes.h>

#include "gpio.h"

#ifndef _BCM2711_UART_H_
#define _BCM2711_UART_H_

/* The one on the Pi is a lot like the one on a PC, other than
 * there's a bunch of MMIO instead of inb/outb stuff.
 */

/* Page 8, BCM2711 peripherals */
typedef enum BCMAuxRegisters
{
	AUX_BASE = BCM2711_PERIPHERAL_BASE + 0x215000,
	AUX_IRQ = AUX_BASE,

	AUX_ENABLES = AUX_BASE + 0x04,

	AUX_MU_IO_REG = AUX_BASE + 0x40,
	AUX_MU_IER_REG = AUX_BASE + 0x44,
	AUX_MU_IIR_REG = AUX_BASE + 0x48,
	AUX_MU_LCR_REG = AUX_BASE + 0x4C,
	AUX_MU_MCR_REG = AUX_BASE + 0x50,
	AUX_MU_LSR_REG = AUX_BASE + 0x54,
	AUX_MU_MSR_REG = AUX_BASE + 0x58,
	AUX_MU_SCRATCH_REG = AUX_BASE + 0x5C,
	AUX_MU_CNTL_REG = AUX_BASE + 0x60,
	AUX_MU_STAT_REG = AUX_BASE + 0x64,
	AUX_MU_BAUD_REG = AUX_BASE + 0x68,
}BCMAuxRegisters;

void BCM_InitUART(VOID);
void BCM2711_WriteUART(const char *Msg);

#endif