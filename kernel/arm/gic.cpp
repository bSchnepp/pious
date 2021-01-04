#include <stdtypes.hpp>

#include <kernel/mmio.hpp>
#include <kernel/arm/gic.hpp>

/**
 * @file kernel/arm/gic.cpp
 * @brief Definitions for managing a GIC device for the aarch64 platform.
 * Most devices typically have some variant of GIC available in them:
 * this code is generic and should support them all, but is tailored and
 * designed for the GIC-400 present in the Raspberry Pi 4B.
 * 
 * Only one GIC class should ever exist at a time, and it should be
 * treated as a singleton class.
 */

/**
 * @brief Initializes this handler for the GIC.
 * @param MMIOAddr The address in physical memory where the GIC is memory
 * mapped.
 */
pious::arm::GIC::GIC(UINT64 MMIOAddr)
{
	this->BaseAddress = MMIOAddr;

	UINT32 NumInterrupts = (this->ReadGIC(
		GIC_CLASS_DISTRIBUTOR, GICD_TYPER, 0) & 0x1F) + 1;

	/* The actual number is 32 * (that). */
	NumInterrupts *= 32;

	for (UINT32 Index = 0; Index < NumInterrupts; ++Index)
	{
		/* Wipe out all the mappings. */
		if (Index % 32 == 0)
		{
			this->WriteGIC(
				GIC_CLASS_DISTRIBUTOR, 
				GICD_ICENABLER, 
				Index / 32, 
				0xFFFFFFFF);

			this->WriteGIC(
				GIC_CLASS_DISTRIBUTOR, 
				GICD_ISCENDR, 
				Index / 32, 
				0xFFFFFFFF);

			/* Always send to CPU0 */
			this->WriteGIC(
				GIC_CLASS_DISTRIBUTOR, 
				GICD_ITARGETSR, 
				Index / 32, 
				0x01010101);

			this->WriteGIC(
				GIC_CLASS_DISTRIBUTOR, 
				GICD_ICACTIVER, 
				Index / 32, 
				0xFFFFFFFF);
		}
	}

	this->WriteGIC(GIC_CLASS_CPU_INTERFACE, GICC_PMR, 0, 0xFF);
}

/**
 * @brief Destroys the current handler for the GIC.
 */
pious::arm::GIC::~GIC()
{

}

/**
 * @author Brian Schnepp
 * @brief Reads an entry from the GIC, based on offsets from the GIC and
 * any further offsets from that location. Note that all values are presumed to 
 * be a 4-byte wide unsigned integer value: if a size of an entry is different,
 * this must be accounted for.
 * 
 * @param Type The type GIC feature to call, such as a hypervisor portion
 * or a descriptor portion.
 * 
 * @param Offset The register to read from the GIC via MMIO
 * 
 * @param ArrayIndex If there is an array offset, then this value corresponds
 * to that. For example, if reading the 3rd entry from some register,
 * offset would be that register, and ArrayIndex will be 3, corresponding
 * to the array index.
 */
UINT32 pious::arm::GIC::ReadGIC(GICClassType Type, 
	GICRegisterOffsets Offset, UINT32 ArrayIndex)
{
	UINT64 Value = this->BaseAddress + Offset + Type + ArrayIndex;
	return ReadMMIOU32(Value);
}

/**
 * @author Brian Schnepp
 * @brief Writes an entry to somewhere managed by the GIC, based on offsets from 
 * the GIC and any further offsets from that location. Note that all values are 
 * presumed to be a 4-byte wide unsigned integer value: if a size of an entry 
 * is different, this must be accounted for.
 * 
 * @param Type The type GIC feature to call, such as a hypervisor portion
 * or a descriptor portion.
 * 
 * @param Offset The register to read from the GIC via MMIO
 * 
 * @param ArrayIndex If there is an array offset, then this value corresponds
 * to that. For example, if reading the 3rd entry from some register,
 * offset would be that register, and ArrayIndex will be 3, corresponding
 * to the array index.
 * 
 * @param Value The value to write at the location given.
 */
VOID pious::arm::GIC::WriteGIC(GICClassType Type, 
	GICRegisterOffsets Offset, UINT32 ArrayIndex, UINT32 Value)
{
	UINT64 Addr = this->BaseAddress + Offset + Type + ArrayIndex;
	WriteMMIOU32(Addr, Value);
}

/**
 * @author Brian Schnepp
 * @brief Instructs the GIC controller to enable itself.
 */
VOID pious::arm::GIC::Enable()
{
	WriteMMIOS32(this->BaseAddress + GIC_CLASS_DISTRIBUTOR + GICD_CTLR, 1);
	WriteMMIOS32(this->BaseAddress + GIC_CLASS_CPU_INTERFACE + GICC_CTLR, 1);
	
}

/**
 * @author Brian Schnepp
 * @brief Instructs the GIC controller to disable itself.
 */
VOID pious::arm::GIC::Disable()
{
	WriteMMIOS32(this->BaseAddress + GIC_CLASS_DISTRIBUTOR + GICD_CTLR, 0);
	WriteMMIOS32(this->BaseAddress + GIC_CLASS_CPU_INTERFACE + GICC_CTLR, 0);
	
}

/**
 * @author Brian Schnepp
 * @brief Loads the interrupt vector table from a specified address, and
 * places it in the appropriate register for the host ARM CPU.
 * 
 * @param Addr The location of the interrupt table
 */
VOID pious::arm::GIC::LIDT(VOID *Addr)
{
	asm volatile("msr vbar_el1, %x[Addr]\n"
		: [Addr]"+r"(Addr));
}

void pious::arm::GIC::ToggleIRQ(BOOL Value)
{
	if (Value)
	{
		asm volatile ("msr daifclr, #2\n");
	} else {
		asm volatile ("msr daifset, #2\n");
	}
}

VOID pious::arm::GIC::EnableInterrupt(UINT32 Interrupt)
{
	UINT32 Interface = Interrupt / 32;
	UINT32 IRQNumber = Interrupt % 32;

	this->WriteGIC(GIC_CLASS_DISTRIBUTOR, 
		GICD_ISENABLER, Interface, (1 << IRQNumber));
}

VOID pious::arm::GIC::DisableInterrupt(UINT32 Interrupt)
{
	UINT32 Interface = Interrupt / 32;
	UINT32 IRQNumber = Interrupt % 32;

	this->WriteGIC(GIC_CLASS_DISTRIBUTOR, 
		GICD_ICENABLER, Interface, (1 << IRQNumber));
}