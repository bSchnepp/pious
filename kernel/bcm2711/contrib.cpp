#include <kern.h>

#include <kernel/arm/gic.hpp>
#include <kernel/bcm2711/fb.hpp>
#include <kernel/bcm2711/uart.hpp>
#include <kernel/bcm2711/timer.hpp>
#include <kernel/bcm2711/contrib.hpp>

void _putchar(char c)
{
	BCM2711_WriteUARTChar(c);
}

static pious::arm::GIC SysGIC(BCM2711_PERIPHERAL_BASE + 0x1840000);





/* According to the documentation, clang is lying about ignoring interrupt
 * attributes. Regardless of who is lying (the compiler or the documentation),
 * boot.S uses a macro to wrap the ISRs anyway, so the problem is moot.
 * The DEFINE_ISR macro implements the code that clang should have generated
 * anyway.
 * 
 * Thus, we can *safely* remove __attribute__((interrupt)) and we're
 * OK. These should be looked into for security holes though, since these blocks
 * of code will be very common to have run...
 */
extern "C"
{

void fiq_handler_el1_sp0()
{
	/* don't care. */
	PIOUS_LOG("%s\n", "fiq_handler_el1_sp0");
}

void err_handler_el1_sp0()
{
	/* don't care. */
	PIOUS_LOG("%s\n", "err_handler_el1_sp0");
}

void syscall_handler_el1_sp0()
{
	/* todo */
	PIOUS_LOG("%s\n", "syscall_handler_el1_sp0");
}

void irq_handler_handler_el1_sp0()
{
	PIOUS_LOG("%s\n", "irq_handler_handler_el1_sp0");
}

void fiq_handler_el1()
{
	/* don't care. */
	PIOUS_LOG("%s\n", "fiq_handler_el1");
}

void err_handler_el1()
{
	/* don't care. */
	PIOUS_LOG("%s\n", "err_handler_el1");
}

void syscall_handler_el1()
{
	/* todo */
	PIOUS_LOG("%s\n", "syscall_handler_el1");
}

void irq_handler_handler_el1()
{
	PIOUS_LOG("%s\n", "irq_handler_handler_el1");
}


void fiq_handler_el0()
{
	/* don't care. */
	PIOUS_LOG("%s\n", "fiq_handler_el0");
}

void err_handler_el0()
{
	/* don't care. */
	PIOUS_LOG("%s\n", "err_handler_el0");
}

void syscall_handler_el0()
{
	/* todo */
	PIOUS_LOG("%s\n", "syscall_handler_el0");
}

void irq_handler_handler_el0()
{
	PIOUS_LOG("%s\n", "irq_handler_handler_el0");
}


/* We don't actually support Aarch32. However, in case something happens
 * in userspace, we'd better do something about these...
 */

void fiq_handler_el0_32()
{
	/* don't care. */
	PIOUS_LOG("%s\n", "fiq_handler_el0_32");
}

void err_handler_el0_32()
{
	/* don't care. */
	PIOUS_LOG("%s\n", "err_handler_el0_32");
}

void syscall_handler_el0_32()
{
	/* todo */
	PIOUS_LOG("%s\n", "syscall_handler_el0_32");
}

void irq_handler_handler_el0_32()
{
	PIOUS_LOG("%s\n", "irq_handler_handler_el0_32");
}

}

extern VOID *interrupt_table;
void StartupSystemPeripherals()
{
	BCM_PrepareFramebuffer(0);
	BCM_InitUART();

	BCM_SetTimerInterval(0, 1000);
	BCM_SetTimerInterval(1, 220000);
	BCM_SetTimerInterval(2, 550000);
	BCM_SetTimerInterval(3, 800000);

	SysGIC.Disable();
	SysGIC.LIDT(interrupt_table);
	SysGIC.Enable();
	SysGIC.ToggleIRQ(TRUE);

	/* GIC's own interrupts */
	SysGIC.EnableInterrupt(0);

	/* System timer */
	SysGIC.EnableInterrupt(3);
}