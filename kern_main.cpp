#include <kernel/mmio.hpp>

#include <kernel/bcm2711/uart.hpp>
#include <kernel/bcm2711/fb.hpp>

#include <kern.h>

/* clang-format: off */
#ifdef __cplusplus
extern "C"
{
#endif

void kern_init(void)
{
	PrepareFramebuffer(0);
	BCM_InitUART();

	PIOUS_LOG("Kernel started. (VER: %d.%d.%d)\n",
		PIOUS_VERSION_MAJOR, PIOUS_VERSION_MINOR, PIOUS_VERSION_PATCH);

	UINT32 Index = 0;
	for (;;)
	{
		for (UINT32 Row = 0; Row < 1080; ++Row)
		{
			for (UINT32 Col = 0; Col < 1920; ++Col)
			{
				UINT32 Color = Index;
				WritePixel(Col, Row, Color);
			}
		}
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