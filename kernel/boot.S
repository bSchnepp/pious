.section ".text.early"
.globl _cpu_start

_cpu_start:
	// Disallow booting for other cores, for now.
	mrs x1, mpidr_el1
	and x1, x1, #3
	cbz x1, maincore
	
	// Spin forever
loop:
	wfe
	b loop
	
maincore:
	// Set up the stack.
	ldr x1, = _cpu_start
	mov sp, x1

	/* Zero out the BSS */
	ldr x1, = bss_begin
	ldr w2, = bss_size

zeroloop:
	cbz w2, endzeroloop
	str xzr, [x1], #8
	sub w2, w2, #1
	cbnz w2, zeroloop

endzeroloop:
	b kern_init
	b loop


.macro DEFINE_ISR func
	/* 272 holds all the registers we'd need to store. */
	sub sp, sp, #272
	
	stp x29, x28, [sp, #0 * 16]
	stp x27, x26, [sp, #1 * 16]
	stp x25, x24, [sp, #2 * 16]
	stp x23, x22, [sp, #3 * 16]
	stp x21, x20, [sp, #4 * 16]
	stp x19, x18, [sp, #5 * 16]
	stp x17, x16, [sp, #6 * 16]
	stp x15, x14, [sp, #7 * 16]
	stp x13, x12, [sp, #8 * 16]
	stp x11, x10, [sp, #9 * 16]
	stp x9, x8, [sp, #10 * 16]
	stp x7, x6, [sp, #11 * 16]
	stp x5, x4, [sp, #12 * 16]
	stp x3, x2, [sp, #13 * 16]
	stp x1, x0, [sp, #14 * 16]

	mrs x0, elr_el1
	mrs x1, spsr_el1
	stp x0, x1, [sp, #15 * 16]

	str x30, [sp, #16 * 16]
	mov x0, sp
	bl \func
	b exit_isr

	/* See exit_isr for details. This is for alignment to 128 bytes. */
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
.endm


exit_isr:
	/* Because of the way ISRs work on aarch64, they must be
	 * exactly 128 bytes. The load-store dance we need to do doesn't
	 * happen to exactly fit, so we need this weird jump exit thing.
	 */
	ldr x30, [sp, #16 * 16]
	ldp x0, x1, [sp, #15 * 16]
	msr spsr_el1, x1
	msr elr_el1, x0

	ldp x1, x0, [sp, #14 * 16]
	ldp x3, x2, [sp, #13 * 16]
	ldp x5, x4, [sp, #12 * 16]
	ldp x7, x6, [sp, #11 * 16]
	ldp x9, x8, [sp, #10 * 16]
	ldp x11, x10, [sp, #9 * 16]
	ldp x13, x12, [sp, #8 * 16]
	ldp x15, x14, [sp, #7 * 16]
	ldp x17, x16, [sp, #6 * 16]
	ldp x19, x18, [sp, #5 * 16]
	ldp x21, x20, [sp, #4 * 16]
	ldp x23, x22, [sp, #3 * 16]
	ldp x25, x24, [sp, #2 * 16]
	ldp x27, x26, [sp, #1 * 16]
	ldp x29, x28, [sp, #0 * 16]

	add sp, sp, #272
	eret


.extern fiq_handler_el1_sp0
.extern err_handler_el1_sp0
.extern syscall_handler_el1_sp0
.extern irq_handler_handler_el1_sp0
.extern fiq_handler_el1
.extern err_handler_el1
.extern syscall_handler_el1
.extern irq_handler_handler_el1
.extern fiq_handler_el0
.extern err_handler_el0
.extern syscall_handler_el0
.extern irq_handler_handler_el0
.extern fiq_handler_el0_32
.extern err_handler_el0_32
.extern syscall_handler_el0_32
.extern irq_handler_handler_el0_32


.globl interrupt_table
interrupt_table:
	DEFINE_ISR fiq_handler_el1_sp0
	DEFINE_ISR err_handler_el1_sp0
	DEFINE_ISR syscall_handler_el1_sp0
	DEFINE_ISR irq_handler_handler_el1_sp0
	DEFINE_ISR fiq_handler_el1
	DEFINE_ISR err_handler_el1
	DEFINE_ISR syscall_handler_el1
	DEFINE_ISR irq_handler_handler_el1
	DEFINE_ISR fiq_handler_el0
	DEFINE_ISR err_handler_el0
	DEFINE_ISR syscall_handler_el0
	DEFINE_ISR irq_handler_handler_el0
	DEFINE_ISR fiq_handler_el0_32
	DEFINE_ISR err_handler_el0_32
	DEFINE_ISR syscall_handler_el0_32
	DEFINE_ISR irq_handler_handler_el0_32