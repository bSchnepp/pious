#include <kern.h>
#include <stdtypes.hpp>
#include <kernel/bcm2711/fb.hpp>

static UINT8 *CurFramebuffer = (UINT8*)NULLPTR;

static UINT8 *Framebuffers[2];

static UINT32 FramebufferWidth = 0;
static UINT32 FramebufferHeight = 0;

static UINT32 FramebufferPitch = 0;
static UINT8 FramebufferOrder = 0;

typedef enum FramebufferOrdering
{
	FRAMEBUFFER_ORDERING_BGR = 0x00,
	FRAMEBUFFER_ORDERING_RGB = 0x01,
}FramebufferOrdering;

/* Get colors ala VGA on a PC. */
UINT32 VGAColors[] = 
{
	0x000000,
	0x0000AA,
	0x00AA00,
	0x00AAAA,

	0xAA0000,
	0xAA00AA,
	0xAA5500,
	0xAAAAAA,
	
	0x555555,
	0x5555FF,
	0x55FF55,
	0x55FFFF,
	
	0xFF5555,
	0xFF55FF,
	0xFFFF55,
	0xFFFFFF
};

VOID BCM_PrepareFramebuffer(UINT8 DisplayIndex)
{
	volatile UINT32 *Mailbox = BorrowMailbox();

	/* 35 entries */
	Mailbox[0] = 35 * sizeof(UINT32);
	Mailbox[1] = BCM_MAILBOX_REQUEST;

	/* Declare that a 1920x1080 framebuffer is desired */
	Mailbox[2] = TAGGING_DETAILED_SETFRAMEBUFFERDIMS;
	Mailbox[3] = 8;
	Mailbox[4] = 8;
	Mailbox[5] = 1920;
	Mailbox[6] = 1080;

	/* Likewise for the virtual framebuffer. */
	Mailbox[7] = TAGGING_DETAILED_SETVFRAMEBUFFERDIMS;
	Mailbox[8] = 8;
	Mailbox[9] = 8;
	Mailbox[10] = 1920;
	Mailbox[11] = 1080;

	/* No offset */
	Mailbox[12] = TAGGING_DETAILED_SETFRAMEBUFFERVOFFSET;
	Mailbox[13] = 8;
	Mailbox[14] = 8;
	Mailbox[15] = 0;
	Mailbox[16] = 0;

	Mailbox[17] = TAGGING_DETAILED_SETFRAMEBUFFERDEPTH;
	Mailbox[18] = 4;
	Mailbox[19] = 4;
	Mailbox[20] = 32;

	Mailbox[21] = TAGGING_DETAILED_SETFRAMEBUFFERPIXORDER;
	Mailbox[22] = 4;
	Mailbox[23] = 4;
	Mailbox[24] = FRAMEBUFFER_ORDERING_RGB;

	Mailbox[25] = TAGGING_DETAILED_MALLOCFRAMEBUFFER;
	Mailbox[26] = 8;
	Mailbox[27] = 8;
	Mailbox[28] = 4096;
	Mailbox[29] = 0;

	Mailbox[30] = TAGGING_DETAILED_GETFRAMEBUFFERPITCH;
	Mailbox[31] = 4;
	Mailbox[32] = 4;
	Mailbox[33] = 0;

	Mailbox[34] = TAGGING_DETAILED_END;

	BCM_CallMailbox(MAILBOX_CHANNEL_PROPERTY_HOST);

	if (Mailbox[20] == 32 && Mailbox[28] != 0)
	{
		UINT64 FramebufferPAddr = Mailbox[28] & 0x3FFFFFFF;

		FramebufferWidth = Mailbox[10];
		FramebufferHeight = Mailbox[11];

		FramebufferOrder = Mailbox[24];
		FramebufferPitch = Mailbox[33];

		Framebuffers[DisplayIndex % 2] = (UINT8*)(FramebufferPAddr);
		CurFramebuffer = Framebuffers[DisplayIndex % 2];
	}

	PIOUS_LOG("Set up framebuffer of %d x %d\n", FramebufferWidth, FramebufferHeight);

	ReleaseMailbox();
}


void BCM_WritePixel(UINT32 Col, UINT32 Row, UINT8 ColorIndex)
{
	UINT32 *FB = (UINT32*)(CurFramebuffer);
	UINT32 Offset = (Row * FramebufferPitch) + (Col * 4);
	FB[Offset] = VGAColors[ColorIndex & 0xF];
}