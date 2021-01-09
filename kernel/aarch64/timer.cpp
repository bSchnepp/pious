#include <kern.h>
#include <stdtypes.hpp>
#include <kernel/aarch64/timer.hpp>



static UINT32 IntervalTime = 0;



VOID pious::arm::TimerEnable()
{
	asm volatile ("msr cntp_cval_el0, %0" :: "r"(0xFFFFFFFFFFFFFFFF));
	asm volatile ("msr cntp_ctl_el0, %0" :: "r"(1ULL));
}

VOID pious::arm::TimerDisable()
{
	asm volatile ("msr cntp_cval_el0, %0" :: "r"(0ULL));
	asm volatile ("msr cntp_ctl_el0, %0" :: "r"(0ULL));
}

VOID pious::arm::TimerSetInterruptInterval(UINT32 Time)
{
	IntervalTime = Time;
}

UINT32 pious::arm::TimerGetInterruptInterval()
{
	return IntervalTime;
}

UINT64 pious::arm::TimerRead()
{
	UINT64 RetVal = 0;
	asm volatile("mrs %x[Val], cntpct_el0\n"
		:
		: [Val]"r"(RetVal));
	return RetVal;
}

UINT64 ClockSpeed = 0;
BOOL pious::arm::TimerWasFired()
{
	/* todo: check if it really was fired... */
	asm volatile("mrs %0, cntfrq_el0\n"
		: "=r"(ClockSpeed));
	asm volatile(
		"msr cntp_tval_el0, %[CS]\n"
		:
		: [CS]"r"(ClockSpeed));
	return TRUE;
}