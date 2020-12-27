#include <kernel/mmio.hpp>

#include <kernel/bcm2711/uart.hpp>
#include <kernel/bcm2711/fb.hpp>

/* clang-format: off */
#ifdef __cplusplus
extern "C"
{
#endif

void kern_init(void)
{
	PrepareFramebuffer(0);

	BCM_InitUART();

	UINT32 Index = 0;
	for (;;)
	{
		for (UINT32 Row = 0; Row < 1080; ++Row)
		{
			for (UINT32 Col = 0; Col < 1920; ++Col)
			{
				UINT32 Color = Index + ((4 * Row) + (4 * Col) % 16);
				WritePixel(Col, Row, Color);
			}
			BCM2711_WriteUART("Hello, world!\n");
		}
		BCM2711_WriteUART("Hi world!\r\n\r\n");
		Index++;
	}

	for (;;)
	{
	}
}

#ifdef __cplusplus
}
#endif
/* clang-format: on */