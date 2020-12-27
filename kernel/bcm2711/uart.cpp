#include <stdtypes.hpp>
#include <kernel/mmio.hpp>

#include <kernel/bcm2711/mailbox.hpp>
#include <kernel/bcm2711/uart.hpp>
#include <kernel/bcm2711/gpio.hpp>

UINT32 BCM_UART_CalculateBaud(UINT32 Value)
{
	/* 500Mhz min clock */
	UINT32 MinSysClock = 500 * 1000 * 1000;
	return (MinSysClock / (Value * 8)) - 1;
}

void BCM_InitUART()
{
	WriteMMIOU32(AUX_ENABLES, 0x01);

	/* Disable everything for now */
	WriteMMIOU32(AUX_MU_IER_REG, 0x00);
	WriteMMIOU32(AUX_MU_CNTL_REG, 0x00);

	/* Use 8-bit mode. FIXME: Try to avoid smashing the reserved parts? */
	WriteMMIOU32(AUX_MU_LCR_REG, 0x03);
	WriteMMIOU32(AUX_MU_MCR_REG, 0x00);

	/* Only bits 2:1 actually matter */
	WriteMMIOU32(AUX_MU_IER_REG, 0x00);
	WriteMMIOU32(AUX_MU_IIR_REG, 0xC6);

	/* Set the baud rate */
	WriteMMIOU32(AUX_MU_BAUD_REG, BCM_UART_CalculateBaud(115200));

	/* Ensure the correct GPIO functions are used. We use pins 14 and 15. */
	SetGPIOFunction(14, BCM2711_GPIO_FUNC_ALT5);
	SetGPIOFunction(15, BCM2711_GPIO_FUNC_ALT5);

	/* Enable recieve and transmission */
	WriteMMIOU32(AUX_MU_CNTL_REG, 0x03);
}

static void BCM2711_WriteChar(char Chr)
{
	UINT32 Unavailable = ReadMMIOU32(AUX_MU_STAT_REG) & 0x20;
	while (Unavailable)
	{
		asm volatile("nop\n");
	}
	WriteMMIOU32(AUX_MU_IO_REG, Chr);
}

void BCM2711_WriteUART(const char *Msg)
{
	UINT64 Index = 0;
	while (Msg[Index] != '\0')
	{
		UINT8 Cur = Msg[Index];
		if (Cur == '\n')
		{
			BCM2711_WriteChar('\r');
		}
		BCM2711_WriteChar(Cur);
		Index++;
	}

}