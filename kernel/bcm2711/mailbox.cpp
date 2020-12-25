#include "gpio.h"
#include "mailbox.h"


volatile unsigned int __attribute__((aligned(16))) Mailbox;

int BCM_CallMailbox(void *Mailbox, BCM2711MailboxChannel Channel)
{
	return 0;
}