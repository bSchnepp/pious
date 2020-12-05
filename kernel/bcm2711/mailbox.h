#ifndef _BCM_2711_MAILBOX_H_
#define _BCM_2711_MAILBOX_H_

/**
 * @file bcm2711/mailbox.h
 * @brief Definitions of the mailbox interface for communication with hardware.
 */

/* https://github.com/raspberrypi/firmware/wiki/Mailboxes */

/**
 * @brief The mailbox tags for hardware communication
 * Note that 'host' and 'device' refer to the host
 * ARM cores and the onboard GPU, respectively, regardless
 * of what ASIC actually brings up the system or manages the other.
 */
typedef enum BCM2711MailboxChannel
{
	MAILBOX_CHANNEL_POWER = 0,
	MAILBOX_CHANNEL_FRAMEBUFFER = 1,
	MAILBOX_CHANNEL_VUART = 2,
	MAILBOX_CHANNEL_VCHIQ = 3,
	MAILBOX_CHANNEL_LEDS = 4,
	MAILBOX_CHANNEL_BTNS = 5,
	MAILBOX_CHANNEL_TOUCH_SCREEN = 6,
	MAILBOX_CHANNEL_UNKNOWN = 7, /* unused??? */
	MAILBOX_CHANNEL_PROPERTY_HOST = 8,
	MAILBOX_CHANNEL_PROPERTYT_DEVICE = 9,
}BCM2711MailboxChannel;


int BCM_CallMailbox(void *Mailbox, BCM2711MailboxChannel Channel);

#endif