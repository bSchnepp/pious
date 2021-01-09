#include <stdtypes.hpp>

#ifndef _PIOUS_ARM_TIMER_HPP_
#define _PIOUS_ARM_TIMER_HPP_

namespace pious::arm
{



VOID TimerEnable();
VOID TimerDisable();

VOID TimerSetInterruptInterval(UINT32 Time);
UINT32 TimerGetInterruptInterval();

UINT64 TimerRead();
BOOL TimerWasFired();


}


#endif