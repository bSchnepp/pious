#include <stdtypes.hpp>
#include <kernel/bcm2711/gpio.hpp>

#ifndef _BCM_2711_TIMER_H_
#define _BCM_2711_TIMER_H_

typedef enum BCM2711Timer
{
	BCM_TIMER_BASE = BCM2711_PERIPHERAL_BASE + 0x3000,
	BCM_TIMER_CS = BCM_TIMER_BASE,

	BCM_TIMER_CLO = BCM_TIMER_BASE + 0x04,
	BCM_TIMER_CLI = BCM_TIMER_BASE + 0x08,

	BCM_TIMER_C0 = BCM_TIMER_BASE + 0x0C,
	BCM_TIMER_C1 = BCM_TIMER_BASE + 0x10,
	BCM_TIMER_C2 = BCM_TIMER_BASE + 0x14,
	BCM_TIMER_C3 = BCM_TIMER_BASE + 0x18,
}BCM2711Timer;

typedef struct BCM2711ControlStatus
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT32 Invalid : 28;
			BOOL SysTimer3 : 1;
			BOOL SysTimer2 : 1;
			BOOL SysTimer1 : 1;
			BOOL SysTimer0 : 1;
		};
	};
}__attribute((__packed__)) BCM2711ControlStatus;

void BCM_SetTimerInterval(UINT8 Slot, UINT32 Interval);
BOOL BCM_CheckSysTimerIRQ(UINT8 Slot);


#endif