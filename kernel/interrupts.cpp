#include <kern.h>
#include <kernel/interrupts.hpp>

extern "C" void __attribute__((interrupt)) UndefinedInstrHandler()
{
	PIOUS_LOG("ERR: %s\n", "Undefined instruction triggered");
	for (;;)
	{
		/* Spin forever and lockup. */
	}
}