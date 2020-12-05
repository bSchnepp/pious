.section ".earlytext"

.global _start

.extern kern_init

_start:
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
