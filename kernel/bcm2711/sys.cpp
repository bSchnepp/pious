#include <kern.h>
#include <kernel/bcm2711/fb.hpp>
#include <kernel/bcm2711/uart.hpp>

#include <kernel/aarch64/timer.hpp>
#include <kernel/aarch64/gic.hpp>

extern "C" void InitCoreSystems()
{
	BCM_InitUART();
	BCM_PrepareFramebuffer(0);
}

extern "C" void InitSystem()
{
	PIOUS_LOG("%s\n", "initsystem");
	UINT64 Addr = BCM2711_PERIPHERAL_BASE + 0x1840000;
	pious::arm::GICSetBaseAddr(Addr);
	PIOUS_LOG("gic base adddress set to %u\n", Addr);
	pious::arm::GICInit();

//	pious::arm::GICEnable();

//	pious::arm::GICEnableInterrupt(27);
//	pious::arm::GICEnableInterrupt(30);

	pious::arm::TimerSetInterruptInterval(250);
	pious::arm::TimerEnable();
}

extern "C" VOID WritePixel(UINT32 Col, UINT32 Row, UINT8 ColorIndex)
{
	BCM_WritePixel(Col, Row, ColorIndex);
}