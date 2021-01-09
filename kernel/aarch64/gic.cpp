#include <kern.h>
#include <stdtypes.hpp>

#include <kernel/mmio.hpp>
#include <kernel/aarch64/gic.hpp>

static UINT64 MMIOAddr;

static UINT8 NumCPUs = 0;
static UINT8 InterruptLines = 0;
static BOOL SecurityExtn = FALSE;

VOID pious::arm::GICSetBaseAddr(UINT64 Address)
{
	MMIOAddr = Address;
}

VOID pious::arm::GICEnable()
{
	PIOUS_LOG("%s\n", "gic enabled");
	WriteMMIOS32(MMIOAddr + GIC_CLASS_DISTRIBUTOR + GICD_CTLR, 1);
	WriteMMIOS32(MMIOAddr + GIC_CLASS_CPU_INTERFACE + GICC_CTLR, 1);

	NumCPUs = (GICRead(GIC_CLASS_DISTRIBUTOR, GICD_TYPER, 0) >> 5) & 0x0F;
	InterruptLines = (GICRead(GIC_CLASS_DISTRIBUTOR, GICD_TYPER, 0) & 0x1F);
	SecurityExtn = (GICRead(GIC_CLASS_DISTRIBUTOR, GICD_TYPER, 0) & 0x1) >> 10;
	PIOUS_LOG("got %hhu cpu interfaces and %hhu lines\n", NumCPUs, InterruptLines);
	PIOUS_LOG("security extensions: %hhu\n", SecurityExtn);

//	asm volatile ("msr daifclr, #15\n");

//	GICWrite(GIC_CLASS_CPU_INTERFACE, GICC_PMR, 0, 0xFF);
//	GICWrite(GIC_CLASS_CPU_INTERFACE, GICC_BPR, 0, 0x00);
}

VOID pious::arm::GICDisable()
{
	GICWrite(GIC_CLASS_CPU_INTERFACE, GICC_PMR, 0, 0x00);
	GICWrite(GIC_CLASS_CPU_INTERFACE, GICC_BPR, 0, 0x00);

	asm volatile ("msr daifset, #15\n");
	WriteMMIOS32(MMIOAddr + GIC_CLASS_CPU_INTERFACE + GICC_CTLR, 0);
	WriteMMIOS32(MMIOAddr + GIC_CLASS_DISTRIBUTOR + GICD_CTLR, 0);
}

UINT32 pious::arm::GICRead(GICClassType Type, 
	GICRegisterOffsets Offset, UINT32 ArrayIndex)
{
	UINT64 Value = MMIOAddr + Offset + Type + ArrayIndex;
	return ReadMMIOU32(Value);
}

VOID pious::arm::GICWrite(GICClassType Type, 
	GICRegisterOffsets Offset, UINT32 ArrayIndex, UINT32 Value)
{
	UINT64 Addr = MMIOAddr + Offset + Type + ArrayIndex;
	WriteMMIOU32(Addr, Value);
}

VOID pious::arm::GICLoadInterruptTable(VOID *Table)
{
	asm volatile("msr vbar_el1, %x[Addr]\n"
		: [Addr]"+r"(Table));
}

VOID pious::arm::GICEnableInterrupt(UINT32 Interrupt)
{
	UINT32 Interface = Interrupt / 32;
	UINT32 IRQNumber = Interrupt % 32;

	GICWrite(GIC_CLASS_DISTRIBUTOR, 
		GICD_ISENABLER, Interface, (1 << IRQNumber));
}

VOID pious::arm::GICDisableInterrupt(UINT32 Interrupt)
{
	UINT32 Interface = Interrupt / 32;
	UINT32 IRQNumber = Interrupt % 32;

	GICWrite(GIC_CLASS_DISTRIBUTOR, 
		GICD_ICENABLER, Interface, (1 << IRQNumber));
}

VOID pious::arm::GICAckInterrupt(UINT32 Interrupt)
{
	UINT32 Interface = Interrupt / 32;
	UINT32 IRQNumber = Interrupt % 32;

	GICWrite(GIC_CLASS_DISTRIBUTOR, 
		GICD_ICPENDR, Interface, (1 << IRQNumber));
}