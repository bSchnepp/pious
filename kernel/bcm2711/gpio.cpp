#include <stdtypes.hpp>

#include <kernel/mmio.hpp>

#include <bcm2711/gpio.hpp>

static VOID CallGPIO(GPIOLocation Loc, UINT32 Value, UINT32 Mask, UINT32 Shift)
{
	/* Check if we've got an impossible request. */
	if (Value > Mask)
	{
		return;
	}

	UINT32 CurVal = ReadMMIOU32(Loc);

	UINT32 Wipeout = ~(Mask << Shift);
	CurVal &= Wipeout;

	/* Write the new value over the old area just wiped out. */
	CurVal |= (Value << Shift);

	/* Commit back to memory. */
	WriteMMIOU32(Loc, CurVal);
}

VOID SetGPIOFunction(UINT16 PinNum, BCM2711PinFunc PinFunc)
{
	GPIOLocation FinalLocation = BCM2711_GPFSEL0;
	UINT8 SelectionOffset = 0;

	GPIOLocation PullLocation = BCM2711_GPIO_PUP_PDN_CNTRL_REG0;
	UINT8 PullOffset = 0;

	/* This can probably be rolled up into a for loop. */
	if (PinNum > 9)
	{
		FinalLocation = BCM2711_GPFSEL1;
		SelectionOffset = 10;
	}
	if (PinNum > 19)
	{
		FinalLocation = BCM2711_GPFSEL2;
		SelectionOffset = 20;
	}
	if (PinNum > 29)
	{
		FinalLocation = BCM2711_GPFSEL3;
		SelectionOffset = 30;
	}
	if (PinNum > 39)
	{
		FinalLocation = BCM2711_GPFSEL4;
		SelectionOffset = 40;
	}
	if (PinNum > 49)
	{
		FinalLocation = BCM2711_GPFSEL5;
		SelectionOffset = 50;
	}

	if (PinNum > 15)
	{
		PullLocation = BCM2711_GPIO_PUP_PDN_CNTRL_REG1;
		PullOffset = 15;
	}
	if (PinNum > 31)
	{
		PullLocation = BCM2711_GPIO_PUP_PDN_CNTRL_REG2;
		PullOffset = 31;
	}
	if (PinNum > 47)
	{
		PullLocation = BCM2711_GPIO_PUP_PDN_CNTRL_REG3;
		PullOffset = 47;
	}

	CallGPIO(FinalLocation, PinFunc, 0b111, (PinNum - SelectionOffset) * 3);
	CallGPIO(PullLocation, BCM2711_PULL_NONE, 0b11, (PinNum - PullOffset) * 2);
}