#include <stdtypes.hpp>

#include <kernel/bcm2711/gpio.hpp>
#include <kernel/bcm2711/mailbox.hpp>

#ifndef _PIOUS_FB_H_
#define _PIOUS_FB_H_

VOID BCM_PrepareFramebuffer(UINT8 DisplayIndex);


void BCM_WritePixel(UINT32 Col, UINT32 Row, UINT8 ColorIndex);


#endif