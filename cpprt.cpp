extern "C"
{

void __cxa_pure_virtual()
{
	/* Do nothing. Possibly warn? */
}

int __cxa_atexit(void (*f)(void*), void *obj, void *dso)
{
	/* ignore */
	return 0;
}

void __cxa_finalize(void *f)
{
	/* Do nothing. */
}

}