#include <kernel/bcm2711/gpio.hpp>
#include <kernel/bcm2711/mailbox.hpp>

volatile unsigned int __attribute__((aligned(16))) Mailbox;

int BCM_CallMailbox(void *Mailbox, BCM2711MailboxChannel Channel)
{
	return 0;
}