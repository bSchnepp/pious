.globl _cpu_start
.extern kern_init

.section ".text.early"
.org 0x80000
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
	ldr x1, =_kern_stack
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
	
.section ".bss"

.global _bss_start
.global _bss_end

_bss_start:
_kern_stack:

.skip (16 * 1024)

_kern_end:
_bss_end:
