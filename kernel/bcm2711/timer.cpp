#include <stdtypes.hpp>
#include <kernel/mmio.hpp>

#include <kernel/bcm2711/gpio.hpp>
#include <kernel/bcm2711/timer.hpp>

static UINT32 Intervals[4] = {0, 0, 0, 0};

void BCM_SetTimerInterval(UINT8 Slot, UINT32 Interval)
{
	UINT32 LowBits = ReadMMIOU32(BCM_TIMER_CLO);
	UINT32 NewVal = LowBits + Interval;
	switch (Slot)
	{
		case 0:
		{
			WriteMMIOU32(BCM_TIMER_C0, NewVal);
			Intervals[0] = Interval;
			break;
		}

		case 1:
		{
			WriteMMIOU32(BCM_TIMER_C1, NewVal);
			Intervals[1] = Interval;
			break;
		}

		case 2:
		{
			WriteMMIOU32(BCM_TIMER_C2, NewVal);
			Intervals[2] = Interval;
			break;
		}

		case 3:
		{
			WriteMMIOU32(BCM_TIMER_C3, NewVal);
			Intervals[3] = Interval;
			break;
		}

		default:
		{
			break;
		}
	}
}

BOOL BCM_CheckSysTimerIRQ(UINT8 Slot)
{
	UINT32 LowBits = ReadMMIOU32(BCM_TIMER_CLO);
	BCM2711ControlStatus Status;
	Status.Raw = ReadMMIOU32(BCM_TIMER_CS);
	switch (Slot)
	{
		case 0:
		{
			/* Is this right??? */
			if (Status.SysTimer0 == 0)
			{
				UINT32 NewVal = LowBits + Intervals[0];
				WriteMMIOU32(BCM_TIMER_C0, NewVal);
				Status.SysTimer0 = 1;
				WriteMMIOU32(BCM_TIMER_CS, Status.Raw);
				return TRUE;
			}
		}

		case 1:
		{
			if (Status.SysTimer1 == 0)
			{
				UINT32 NewVal = LowBits + Intervals[1];
				WriteMMIOU32(BCM_TIMER_C1, NewVal);
				Status.SysTimer1 = 1;
				WriteMMIOU32(BCM_TIMER_CS, Status.Raw);
				return TRUE;
			}
		}

		case 2:
		{
			if (Status.SysTimer2 == 0)
			{
				UINT32 NewVal = LowBits + Intervals[2];
				WriteMMIOU32(BCM_TIMER_C2, NewVal);
				Status.SysTimer2 = 1;
				WriteMMIOU32(BCM_TIMER_CS, Status.Raw);
				return TRUE;
			}
		}

		case 3:
		{
			if (Status.SysTimer3 == 0)
			{
				UINT32 NewVal = LowBits + Intervals[3];
				WriteMMIOU32(BCM_TIMER_C3, NewVal);
				Status.SysTimer3 = 1;
				WriteMMIOU32(BCM_TIMER_CS, Status.Raw);
				return TRUE;
			}
		}

		default:
		{
			return FALSE;
		}
	}
	return FALSE;
}