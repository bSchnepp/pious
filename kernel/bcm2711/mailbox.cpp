//#include <atomic>

#include <kernel/mmio.hpp>
#include <kernel/bcm2711/gpio.hpp>
#include <kernel/bcm2711/mailbox.hpp>


//static std::atomic_bool MailboxAvailable;
static bool MailboxAvailable = TRUE;
static volatile UINT32 __attribute__((aligned(16))) Mailbox[36];

UINT32 BCM_CallMailbox(BCM2711MailboxChannel Channel)
{
	while (ReadMMIOU32(BCM2711_VIDEOCORE_MBOXONE_STATUS) & BCM_MAILBOX_FULL)
	{
	}

	UINT32 RawPAddr = ((UINT32)((UINT64)&Mailbox) & ~0xF) | (Channel & 0xF);

	WriteMMIOU32(BCM2711_VIDEOCORE_MBOXONE_WRITE, RawPAddr);

	for (;;)
	{
		UINT32 MBoxStatus = 0;
		do
		{
			MBoxStatus = ReadMMIOU32(BCM2711_VIDEOCORE_MBOXONE_STATUS);
		} while(MBoxStatus & BCM2711_VIDEOCORE_MBOXONE_STATUS);

		if (RawPAddr == ReadMMIOU32(BCM2711_VIDEOCORE_MBOXONE_READ))
		{
			/* Signal that this is a response. */
			return Mailbox[1] == 0x80000000;
		}
	}
	return 0;
}

volatile UINT32 *BorrowMailbox()
{
	bool Lock = true;
	while (Lock == true)
	{
		MailboxAvailable = false;
		break;
	}
	return Mailbox;
}

VOID ReleaseMailbox()
{
	bool Lock = false;
	while (Lock == false)
	{
		MailboxAvailable = true;
		break;
	}
}