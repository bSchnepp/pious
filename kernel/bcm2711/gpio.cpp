#include <stdtypes.h>

#include <kernel/mmio.hpp>

#include <bcm2711/gpio.hpp>

static VOID CallGPIO(UINT16 PinNum, UINT32 Value, UINT32 Base, UINT32 FieldSz)
{
	UINT32 Mask = (0x01 << FieldSz) - 1;

	if (PinNum > BCM2711_MAX_PIN)
	{
		return;
	}

	if (Value > Mask)
	{
		return;
	}

	/* Some encoding needs to happen for MMIO to work. */
	UINT32 FieldCnt = (32 / FieldSz);
	UINT32 Reg = Base + ((PinNum / FieldCnt) * 4);
	UINT32 Shift = FieldSz * (PinNum % FieldCnt);

	UINT32 CurVal = ReadMMIOU32(Reg);
	CurVal &= ~(Mask << Shift);
	CurVal |= (Value << Shift);
	WriteMMIOU32(Reg, CurVal);
}

VOID SetGPIOFunction(UINT16 PinNum, BCM2711PinUse Usage, BCM2711PinFunc PinFunc)
{
	CallGPIO(PinNum, Usage, BCM2711_GPIO_PUP_PDN_CNTRL_REG0, 2);
	CallGPIO(PinNum, PinFunc, BCM2711_GPFSEL0, 3);
}