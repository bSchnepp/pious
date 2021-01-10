#include <stdtypes.hpp>

#ifndef _BCM2711_SYS_HPP_
#define _BCM2711_SYS_HPP_

extern "C"
{

VOID InitCoreSystems();
VOID InitSystem();

VOID WritePixel(UINT32 Col, UINT32 Row, UINT8 ColorIndex);

}

#endif