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
	/* We need to borrow the mailbox. */
	volatile UINT32 *Mailbox = BorrowMailbox();

	/* Let's use the UART0 instead. */
	/* Start by disabling the UART */
	WriteMMIOU32(UART0_CTRL_REG, 0);


	/* We'll need 9 fields. */
	Mailbox[0] = 9 * sizeof(UINT32);
	Mailbox[1] = BCM_MAILBOX_REQUEST;
	Mailbox[2] = TAGGING_DETAILED_SETCLOCKRATE;
	Mailbox[3] = 12; /* Entry is 12 bytes long */
	Mailbox[4] = 8; /* Response is 8 */
	Mailbox[5] = 2; /* UART0 clock is 2. */
	Mailbox[6] = 4 * 1000 * 1000; /* 4Mhz clock */
	Mailbox[7] = 0; /* Disable turbo */
	Mailbox[8] = TAGGING_DETAILED_END;

	/* Call the mailbox. */
	BCM_CallMailbox(MAILBOX_CHANNEL_PROPERTY_HOST);

	/* We want UART0. */
	SetGPIOFunction(14, BCM2711_GPIO_FUNC_ALT0);
	SetGPIOFunction(15, BCM2711_GPIO_FUNC_ALT0);

	/* Wipe out interrupts. */
	UARTInterruptClear Ints;
	Ints.Raw = 0x7FF;
	WriteMMIOU32(UART0_INT_CLR_REG, Ints.Raw);

	UARTIntBaudReg IntBaud;
	IntBaud.IntBaud = 2;
	WriteMMIOU32(UART0_INT_BAUD_REG, IntBaud.Raw);

	UARTFractBaudReg FractBaud;
	FractBaud.Fraction = 0b1011;
	WriteMMIOU32(UART0_FRACT_BAUD_REG, FractBaud.Raw);

	UARTLineControlReg LineCtrl;
	LineCtrl.SPS = FALSE; /* Disable stick parity */
	LineCtrl.WLEN = 0b11; /* 8 bit data */
	WriteMMIOU32(UART0_LINE_CTRL_REG, LineCtrl.Raw);

	/* Re-enable the UART. */
	UARTControlReg Control;
	Control.TXE = TRUE;
	Control.RXE = TRUE;
	Control.ENABLE = TRUE;
	WriteMMIOU32(UART0_CTRL_REG, Control.Raw);
		
	/* Go ahead and release the mailbox. */
	ReleaseMailbox();
}

static void BCM2711_WriteChar(char Chr)
{
	UINT32 Unavailable = ReadMMIOU32(UART0_FLAG_REG) & 0x20;
	while (Unavailable)
	{
		asm volatile("nop\n");
	}
	WriteMMIOU32(UART0_DATA_REG, Chr);
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