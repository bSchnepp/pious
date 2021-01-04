#include <stdtypes.hpp>

#ifndef _PIOUS_MUTEX_HPP_
#define _PIOUS_MUTEX_HPP_

namespace pious
{

template <typename T>
class mutex
{
public:
	mutex(T &Item)
	{
		this->Item = &Item;
		this->Locked = false;
	}

	~mutex()
	{
		this->Locked = false;
	}

	void lock()
	{
		while (__sync_bool_compare_and_swap(&(this->Locked), false, true))
		{
		}
	}

	void unlock()
	{
		while (__sync_bool_compare_and_swap(&(this->Locked), true, false))
		{
		}
	}

	T& operator*()
	{
		return *(this->Item);
	}

private:
	bool Locked;
	T *Item;

};

}
#endif