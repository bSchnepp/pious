#include "mailbox.h"

#define BCM2711_MMIO_PADDR (0xFE000000)

#define BCM2711_MMIO_READ(x) ((volatile unsigned int *)(BCM2711_MMIO_PADDR + 0x00))
#define BCM2711_MMIO_POLL(x) ((volatile unsigned int *)(BCM2711_MMIO_PADDR + 0x10))
#define BCM2711_MMIO_SENDER(x) ((volatile unsigned int *)(BCM2711_MMIO_PADDR + 0x14))
#define BCM2711_MMIO_STATUS(x) ((volatile unsigned int *)(BCM2711_MMIO_PADDR + 0x18))
#define BCM2711_MMIO_CONFIG(x) ((volatile unsigned int *)(BCM2711_MMIO_PADDR + 0x1C))
#define BCM2711_MMIO_WRITE(x) ((volatile unsigned int *)(BCM2711_MMIO_PADDR + 0x20))

volatile unsigned int __attribute__((aligned(16))) Mailbox;

int BCM_CallMailbox(void *Mailbox, BCM2711MailboxChannel Channel)
{
	return 0;
}