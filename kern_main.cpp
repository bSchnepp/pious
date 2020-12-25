#include <kernel/bcm2711/uart.h>

/* clang-format: off */
#ifdef __cplusplus
extern "C"
{
#endif

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

#ifdef __cplusplus
}
#endif
/* clang-format: on */