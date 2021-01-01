#include <kernel/arm/gic.hpp>
#include <kernel/bcm2711/fb.hpp>
#include <kernel/bcm2711/uart.hpp>
#include <kernel/bcm2711/contrib.hpp>

void _putchar(char c)
{
	BCM2711_WriteUARTChar(c);
}

static pious::arm::GIC SysGIC(BCM2711_PERIPHERAL_BASE + 0x1840000);





/* According to the documentation, clang is lying about ignoring these
 * attributes. We'll need to validate with radare or objdump later,
 * and if it really is ignoring it, complain to llvm upstream.
 * (ie, this is probably a clang bug)
 * 
 * https://clang.llvm.org/docs/AttributeReference.html#interrupt-arm
 */
extern "C"
{
/* We'll need to set up some reset vectors... */

void __attribute__((interrupt("FIQ"))) fiq_handler_el1_sp0()
{
	/* don't care. */
}

void __attribute__((interrupt("ABORT"))) err_handler_el1_sp0()
{
	/* don't care. */
}

void __attribute__((interrupt("SWI"))) syscall_handler_el1_sp0()
{
	/* todo */
}

void __attribute__((interrupt("IRQ"))) irq_handler_handler_el1_sp0()
{
	/* todo */
}

void __attribute__((interrupt("FIQ"))) fiq_handler_el1()
{
	/* don't care. */
}

void __attribute__((interrupt("ABORT"))) err_handler_el1()
{
	/* don't care. */
}

void __attribute__((interrupt("SWI"))) syscall_handler_el1()
{
	/* todo */
}

void __attribute__((interrupt("IRQ"))) irq_handler_handler_el1()
{
	/* todo */
}


void __attribute__((interrupt("FIQ"))) fiq_handler_el0()
{
	/* don't care. */
}

void __attribute__((interrupt("ABORT"))) err_handler_el0()
{
	/* don't care. */
}

void __attribute__((interrupt("SWI"))) syscall_handler_el0()
{
	/* todo */
}

void __attribute__((interrupt("IRQ"))) irq_handler_handler_el0()
{
	/* todo */
}


/* We don't actually support Aarch32. However, in case something happens
 * in userspace, we'd better do something about these...
 */

void __attribute__((interrupt("FIQ"))) fiq_handler_el0_32()
{
	/* don't care. */
}

void __attribute__((interrupt("ABORT"))) err_handler_el0_32()
{
	/* don't care. */
}

void __attribute__((interrupt("SWI"))) syscall_handler_el0_32()
{
	/* todo */
}

void __attribute__((interrupt("IRQ"))) irq_handler_handler_el0_32()
{
	/* todo */
}

}

void StartupSystemPeripherals()
{
	PrepareFramebuffer(0);
	BCM_InitUART();

	SysGIC.Disable();

	/* Set it up here... */

//	GIC.Enable();
}