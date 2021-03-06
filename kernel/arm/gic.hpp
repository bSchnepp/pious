#include <stdtypes.hpp>

#ifndef _PIOUS_ARM_GIC_HPP_
#define _PIOUS_ARM_GIC_HPP_

namespace pious
{

namespace arm
{

typedef enum GICClassType
{
	GIC_CLASS_DISTRIBUTOR = 0x1000,
	GIC_CLASS_CPU_INTERFACE = 0x2000,
	GIC_CLASS_VIRTUAL_CONTROL = 0x4000,
	GIC_CLASS_VIRTUAL_CPU = 0x5000,
}GICClassType;

typedef enum GICRegisterOffsets
{
	/*  Distributor register map */
	GICD_CTLR = 0x00,
	GICD_TYPER = 0x04,
	GICD_IIDR = 0x08,

	/* Array of 32 registers each */
	GICD_IGROUPR = 0x080,
	GICD_ISENABLER = 0x100,
	GICD_ICENABLER = 0x180,
	GICD_ISPENDR = 0x200,
	GICD_ISCENDR = 0x280,
	GICD_ISACTIVER = 0x300,
	GICD_ICACTIVER = 0x380,
	GICD_IPRIORITYR = 0x400,

	GICD_ITARGETSR = 0x800,
	GICD_ICFGR = 0xC00,

	GICD_NSCAR = 0xE00,
	GICD_SGIR = 0xF00,

	GICD_CPENDSGIR = 0xF10,
	GICD_SPENDSGIR = 0xF20,

	/* CPU interface register map */
	GICC_CTLR = 0x00,
	GICC_PMR = 0x04,
	GICC_BPR = 0x08,
	GICC_IAR = 0x0C,
	GICC_EOIR = 0x10,
	GICC_RPR = 0x14,
	GICC_HPPIR = 0x18,
	GICC_ABPR = 0x1C,
	GICC_AIAR = 0x20,
	GICC_AEOIR = 0x24,
	GICC_AHPPIR = 0x28,
	GICC_APR = 0xD0,
	GICC_NSAPR = 0xE0,
	GICC_IIDR = 0xFC,
	GICC_DIR = 0x1000,

	/* Hypervisor stuff */
	GICH_HCR = 0x00,
	GICH_VTR = 0x04,
	GICH_VMCR = 0x08,
	GICH_MISR = 0x10,
	GICH_EISR0 = 0x20,
	GICH_EISR1 = 0x24,
	GICH_ELSR0 = 0x30,
	GICH_ELSR1 = 0x34,
	GICH_APR = 0xF0,
	GICH_LR = 0x100,

	GICV_CTLR = 0x00,
	GICV_PMR = 0x04,
	GICV_BPR = 0x08,
	GICV_IAR = 0x0C,
	GICV_EOIR = 0x10,
	GICV_RPR = 0x14,
	GICV_HPPIR = 0x18,
	GICV_ABPR = 0x1C,
	GICV_AIAR = 0x20,
	GICV_AEOIR = 0x24,
	GICV_AHPPIR = 0x28,
	GICV_APR = 0xD0,
	GICV_IIDR = 0xFC,
	GICV_DIR = 0x1000,
}GICRegisterOffsets;

class GIC
{

public: 
	GIC(UINT64 MMIOAddr);
	~GIC();

	VOID Enable();
	VOID Disable();

	UINT32 ReadGIC(GICClassType Type, 
		GICRegisterOffsets Offset, UINT32 ArrayIndex);

	VOID WriteGIC(GICClassType Type, 
		GICRegisterOffsets Offset, UINT32 ArrayIndex, UINT32 Value);

	VOID LIDT(VOID *Table);

	VOID ToggleIRQ(BOOL Value);

	VOID EnableInterrupt(UINT32 Interrupt);
	VOID DisableInterrupt(UINT32 Interrupt);

private:
	UINT64 BaseAddress;
};

}

}

#endif