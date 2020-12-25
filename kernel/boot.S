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