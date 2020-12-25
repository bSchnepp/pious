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
	UINT32 Index = 0;
	for (;;)
	{
		for (UINT32 Col = 0; Col < 1920; ++Col)
		{
			for (UINT32 Row = 0; Row < 1080; ++Row)
			{
				WritePixel(Col, Row, (Index + Col));
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