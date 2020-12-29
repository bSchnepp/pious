#include <kernel/arm/gic.hpp>
#include <kernel/bcm2711/fb.hpp>
#include <kernel/bcm2711/uart.hpp>
#include <kernel/bcm2711/contrib.hpp>

void _putchar(char c)
{
	BCM2711_WriteUARTChar(c);
}

static pious::arm::GIC SysGIC(BCM2711_PERIPHERAL_BASE + 0x1840000);

void StartupSystemPeripherals()
{
	PrepareFramebuffer(0);
	BCM_InitUART();
	
	SysGIC.Disable();

	/* Set it up here... */

//	GIC.Enable();
}