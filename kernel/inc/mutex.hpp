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
		while (this->Locked == false)
		{
			this->Locked = true;
		}
	}

	void unlock()
	{
		while (this->Locked == true)
		{
			this->Locked = false;
		}		
	}

	T& operator*()
	{
		return *(this->Item);
	}

private:
	/* Temporary: atomic doesn't work?
	 *
	 * Some trickery with enforcing *strong* memory model is required.
	 * Otherwise we might have a data race happen where the core decides
	 * it's OK to reorder RAM commits to have this done after the actual
	 * check, so sometimes we might borrow twice which is invalid.
	 * 
	 * <atomic> doesn't seem defined (which is why I wanted C++ anyway...),
	 * and the corresponding C11 header stdatomic seems to cause some
	 * crash. Without JTAG or at least getting miniuart to work, this is
	 * very hard to debug why.
	 */
	bool Locked;
	T *Item;

};

}
#endif