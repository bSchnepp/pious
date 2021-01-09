#include <kern.h>

extern "C"
{

void __cxa_pure_virtual()
{
	/* Do nothing. Possibly warn? */
}

int __cxa_atexit(void (*f)(void*), void *obj, void *dso)
{
	/* ignore */
	PIOUS_UNUSED(f);
	PIOUS_UNUSED(obj);
	PIOUS_UNUSED(dso);
	return 0;
}

void __cxa_finalize(void *f)
{
	/* Do nothing. */
	PIOUS_UNUSED(f);
}

}