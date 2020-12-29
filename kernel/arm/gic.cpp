#include <stdtypes.hpp>

#include <kernel/mmio.hpp>
#include <kernel/arm/gic.hpp>

pious::arm::GIC::GIC(UINT64 MMIOAddr)
{
	this->BaseAddress = MMIOAddr;
}

pious::arm::GIC::~GIC()
{

}

UINT32 pious::arm::GIC::ReadGIC(GICClassType Type, 
	GICRegisterOffsets Offset, UINT32 ArrayIndex)
{
	UINT64 Value = this->BaseAddress + Offset + Type + ArrayIndex;
	return ReadMMIOU32(Value);
}

VOID pious::arm::GIC::WriteGIC(GICClassType Type, 
	GICRegisterOffsets Offset, UINT32 ArrayIndex, UINT32 Value)
{
	/* nyi */
}

VOID pious::arm::GIC::Enable()
{
	WriteMMIOS32(this->BaseAddress + GIC_CLASS_DISTRIBUTOR + GICD_CTLR, 1);
	WriteMMIOS32(this->BaseAddress + GIC_CLASS_CPU_INTERFACE + GICC_CTLR, 1);
}

VOID pious::arm::GIC::Disable()
{
	WriteMMIOS32(this->BaseAddress + GIC_CLASS_DISTRIBUTOR + GICD_CTLR, 0);
	WriteMMIOS32(this->BaseAddress + GIC_CLASS_CPU_INTERFACE + GICC_CTLR, 0);
}