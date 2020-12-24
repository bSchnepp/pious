#include <kernel/bcm2711/uart.h>

void kern_init(void)
{
	BCM_InitUART();
	BCM2711_WriteUART("\n");
	BCM2711_WriteUART("Hello, world!\n");
	BCM2711_WriteUART("\n");
	BCM2711_WriteUART("Hello, world!!\n");
	BCM2711_WriteUART("\n");
	for (;;)
	{
	}
}
