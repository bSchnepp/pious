#include <kern.h>
#include <stdtypes.hpp>

#ifndef _PIOUS_MUTEX_HPP_
#define _PIOUS_MUTEX_HPP_

namespace pious
{

typedef bool mutex;

inline void lock(mutex *mut)
{
	while (__sync_bool_compare_and_swap(mut, false, true))
	{
	}
}

inline void unlock(mutex *mut)
{
	while (__sync_bool_compare_and_swap(mut, true, false))
	{
	}
}

}
#endif