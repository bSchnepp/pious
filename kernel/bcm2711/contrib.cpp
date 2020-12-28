#include <kernel/bcm2711/uart.hpp>
#include <kernel/bcm2711/contrib.hpp>

void _putchar(char c)
{
	BCM2711_WriteUARTChar(c);
}