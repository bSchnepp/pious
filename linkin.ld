ENTRY(_cpu_start)

SECTIONS
{
	/* aarch64 load address */
	. = 0x80000;

	.text :
	{
		*(.text.early)
		*(.text.ext)
		*(.text)
	}
	
	.rodata :
	{
		*(.rodata*)
	}
	
	.data :
	{
		*(.data*)
	}
	
	bss_begin = .;
	.bss :
	{
		*(.bss*)
	}
	bss_end = .;
	bss_size = bss_end - bss_begin;

	/DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
	
}
