ENTRY(_start)

SECTIONS
{
	/* aarch64 load address */
	. = 0x80000;
	
	
	.earlytext :
	{
		*(.earlytext)
	}
	
	.text :
	{
		*(.text*)
	}
	
	.rodata :
	{
		*(.rodata*)
	}
	
	.data :
	{
		*(.data*)
	}
	
	.bss :
	{
		*(.bss*)
	}
	
}
