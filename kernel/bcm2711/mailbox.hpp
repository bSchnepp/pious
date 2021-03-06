#include <stdtypes.hpp>
#include <kernel/bcm2711/gpio.hpp>

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


typedef enum BCM2711Tagging
{
	TAGGING_FIRMWARE = (0x0000 << 16),
	TAGGING_HARDWARE = (0x0001 << 16),
	TAGGING_POWER = (0x0002 << 16),
	TAGGING_CLOCK = (0x0003 << 16),
	TAGGING_FRAMEBUFFER = (0x0004 << 16),
	TAGGING_COMMAND_LINE = (0x0005 << 16),
	TAGGING_SHARED = (0x0006 << 16),
}BCM2711Tagging;

typedef enum BCM2711TaggingSpecific
{
	TAGGING_DETAILED_END = 0x00000000,
	/* Firmware stuff */
	TAGGING_DETAILED_GETFIRMWAREVERSION = TAGGING_FIRMWARE | 0x0001,
	TAGGING_DETAILED_SETCURSORINFO = TAGGING_FIRMWARE | 0x8010,
	TAGGING_DETAILED_SETCURSORSTATE = TAGGING_FIRMWARE | 0x8011,

	/* Hardware stuff */
	TAGGING_DETAILED_GETBOARDMODEL = TAGGING_HARDWARE | 0x0001,
	TAGGING_DETAILED_GETBOARDREVISION = TAGGING_HARDWARE | 0x0002,
	TAGGING_DETAILED_GETBOARDMACADDRESS = TAGGING_HARDWARE | 0x0003,
	TAGGING_DETAILED_GETBOARDSERIAL = TAGGING_HARDWARE | 0x0004,
	TAGGING_DETAILED_GETARMMEMORY = TAGGING_HARDWARE | 0x0005,
	TAGGING_DETAILED_GETVCMEMORY = TAGGING_HARDWARE | 0x0006,
	TAGGING_DETAILED_GETCLOCKS = TAGGING_HARDWARE | 0x0007,

	/* Power state */
	TAGGING_DETAILED_GETPOWERSTATE = TAGGING_POWER | 0x0001,
	TAGGING_DETAILED_GETPOWERTIMING = TAGGING_POWER | 0x0002,
	TAGGING_DETAILED_SETPOWERSTATE = TAGGING_POWER | 0x8001,

	/* System clock related stuff */
	TAGGING_DETAILED_GETCLOCKSTATE = TAGGING_CLOCK | 0x0001,
	TAGGING_DETAILED_SETCLOCKSTATE = TAGGING_CLOCK | 0x8001,
	TAGGING_DETAILED_GETCLOCKRATE = TAGGING_CLOCK | 0x0002,
	TAGGING_DETAILED_SETCLOCKRATE = TAGGING_CLOCK | 0x8002,
	TAGGING_DETAILED_GETMAXCLOCKRATE = TAGGING_CLOCK | 0x0004,
	TAGGING_DETAILED_GETMINCLOCKRATE = TAGGING_CLOCK | 0x0007,
	TAGGING_DETAILED_GETTURBO = TAGGING_CLOCK | 0x0009,
	TAGGING_DETAILED_SETTURBO = TAGGING_CLOCK | 0x8009,

	/* Oddly enough, these use the clock field, but are power stuff. */
	TAGGING_DETAILED_GETVOLTAGE = TAGGING_CLOCK | 0x0003,
	TAGGING_DETAILED_SETVOLTAGE = TAGGING_CLOCK | 0x8003,

	TAGGING_DETAILED_GETMAXVOLTAGE = TAGGING_CLOCK | 0x0005,
	TAGGING_DETAILED_GETMINVOLTAGE = TAGGING_CLOCK | 0x0008,

	/* This is some temperture stuff... */
	TAGGING_DETAILED_GETTEMPERTURE = TAGGING_CLOCK | 0x0006,
	TAGGING_DETAILED_GETMAXTEMPERTURE = TAGGING_CLOCK | 0x000a,

	/* And then some GPU stuff. */
	TAGGING_DETAILED_MALLOCGPUMEM = TAGGING_CLOCK | 0x000c,
	TAGGING_DETAILED_LOCKGPUMEM = TAGGING_CLOCK | 0x000d,
	TAGGING_DETAILED_UNLOCKGPUMEM = TAGGING_CLOCK | 0x000e,
	TAGGING_DETAILED_FREEGPUMEM = TAGGING_CLOCK | 0x0010,
	
	/* Display stuff */
	TAGGING_DETAILED_DISPMANXRESOURCE = TAGGING_CLOCK | 0x0014,
	TAGGING_DETAILED_GETEDID = TAGGING_CLOCK | 0x0020,

	/* And now for framebuffer stuff. */
	TAGGING_DETAILED_MALLOCFRAMEBUFFER = TAGGING_FRAMEBUFFER | 0x0001,
	TAGGING_DETAILED_FREEFRAMEBUFFER = TAGGING_FRAMEBUFFER | 0x8001,
	TAGGING_DETAILED_CLEARFRAMEBUFFER = TAGGING_FRAMEBUFFER | 0x0002,

	/* These are the framebuffer allocated. */
	TAGGING_DETAILED_GETFRAMEBUFFERDIMS = TAGGING_FRAMEBUFFER | 0x0003,
	TAGGING_DETAILED_TESTFRAMEBUFFERDIMS = TAGGING_FRAMEBUFFER | 0x4003,
	TAGGING_DETAILED_SETFRAMEBUFFERDIMS = TAGGING_FRAMEBUFFER | 0x8003,

	/* These are the ones actually sent, which isn't the same if things
	 * like panning are done.
	 */
	TAGGING_DETAILED_GETVFRAMEBUFFERDIMS = TAGGING_FRAMEBUFFER | 0x0004,
	TAGGING_DETAILED_TESTVFRAMEBUFFERDIMS = TAGGING_FRAMEBUFFER | 0x4004,
	TAGGING_DETAILED_SETVFRAMEBUFFERDIMS = TAGGING_FRAMEBUFFER | 0x8004,

	/* And for bit depth... */
	TAGGING_DETAILED_GETFRAMEBUFFERDEPTH = TAGGING_FRAMEBUFFER | 0x0005,
	TAGGING_DETAILED_TESTFRAMEBUFFERDEPTH = TAGGING_FRAMEBUFFER | 0x4005,
	TAGGING_DETAILED_SETFRAMEBUFFERDEPTH = TAGGING_FRAMEBUFFER | 0x8005,

	/* And for the pixel order (ABGR or ARGB) */
	TAGGING_DETAILED_GETFRAMEBUFFERPIXORDER = TAGGING_FRAMEBUFFER | 0x0006,
	TAGGING_DETAILED_TESTFRAMEBUFFERPIXORDER = TAGGING_FRAMEBUFFER | 0x4006,
	TAGGING_DETAILED_SETFRAMEBUFFERPIXORDER = TAGGING_FRAMEBUFFER | 0x8006,

	TAGGING_DETAILED_GETFRAMEBUFFERALPHA = TAGGING_FRAMEBUFFER | 0x0007,
	TAGGING_DETAILED_TESTFRAMEBUFFERALPHA = TAGGING_FRAMEBUFFER | 0x4007,
	TAGGING_DETAILED_SETFRAMEBUFFERALPHA = TAGGING_FRAMEBUFFER | 0x8007,

	TAGGING_DETAILED_GETFRAMEBUFFERPITCH = TAGGING_FRAMEBUFFER | 0x0008,

	TAGGING_DETAILED_GETFRAMEBUFFERVOFFSET = TAGGING_FRAMEBUFFER | 0x0009,
	TAGGING_DETAILED_TESTFRAMEBUFFERVOFFSET = TAGGING_FRAMEBUFFER | 0x4009,
	TAGGING_DETAILED_SETFRAMEBUFFERVOFFSET = TAGGING_FRAMEBUFFER | 0x8009,

	TAGGING_DETAILED_GETFRAMEBUFFEROVERSCAN = TAGGING_FRAMEBUFFER | 0x000a,
	TAGGING_DETAILED_TESTFRAMEBUFFEROVERSCAN = TAGGING_FRAMEBUFFER | 0x400a,
	TAGGING_DETAILED_SETFRAMEBUFFEROVERSCAN = TAGGING_FRAMEBUFFER | 0x800a,

	TAGGING_DETAILED_GETFRAMEBUFFERPALLETE = TAGGING_FRAMEBUFFER | 0x000b,
	TAGGING_DETAILED_TESTFRAMEBUFFERPALLETE = TAGGING_FRAMEBUFFER | 0x400b,
	TAGGING_DETAILED_SETFRAMEBUFFERPALLETE = TAGGING_FRAMEBUFFER | 0x800b,

	/* And for the bootloader's command line. */
	TAGGING_DETAILED_GETCOMMANDLINE = TAGGING_COMMAND_LINE | 0x0001,

	/* DMA stuff */
	TAGGING_DETAILED_GETDMACHANNELS = TAGGING_SHARED | 0x0001,
}BCM2711TaggingSpecific;

typedef enum BCM2711Mailbox1Reg
{
	BCM2711_VIDEOCORE_MBOXONE = BCM2711_PERIPHERAL_BASE + 0xB880,
	BCM2711_VIDEOCORE_MBOXONE_READ = BCM2711_VIDEOCORE_MBOXONE + 0x00,
	BCM2711_VIDEOCORE_MBOXONE_POLL = BCM2711_VIDEOCORE_MBOXONE + 0x10,
	BCM2711_VIDEOCORE_MBOXONE_SENDER = BCM2711_VIDEOCORE_MBOXONE + 0x14,
	BCM2711_VIDEOCORE_MBOXONE_STATUS = BCM2711_VIDEOCORE_MBOXONE + 0x18,
	BCM2711_VIDEOCORE_MBOXONE_CONFIG = BCM2711_VIDEOCORE_MBOXONE + 0x1C,
	BCM2711_VIDEOCORE_MBOXONE_WRITE = BCM2711_VIDEOCORE_MBOXONE + 0x20,
}BCM2711Mailbox1Reg;


typedef enum BCM2711MailboxStatus
{
	BCM_MAILBOX_EMPTY = 0x00000000,
	BCM_MAILBOX_FULL = 0x80000000,
}BCM2711MailboxStatus;

typedef enum BCM2711MailboxTagType
{
	BCM_MAILBOX_REQUEST = 0,
}BCM2711MailboxTagType;


volatile UINT32 *BorrowMailbox();
VOID ReleaseMailbox();
UINT32 BCM_CallMailbox(BCM2711MailboxChannel Channel);

#endif