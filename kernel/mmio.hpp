#include <stdtypes.hpp>

#ifndef _PIOUS_MMIO_H_
#define _PIOUS_MMIO_H_

/* clang-format: off */
#ifdef __cplusplus
extern "C"
{
#endif

VOID WriteMMIOU64(UINT64 Addr, UINT64 Value);
VOID WriteMMIOU32(UINT64 Addr, UINT32 Value);
VOID WriteMMIOU16(UINT64 Addr, UINT16 Value);
VOID WriteMMIOU8(UINT64 Addr, UINT8 Value);

VOID WriteMMIOS64(UINT64 Addr, INT64 Value);
VOID WriteMMIOS32(UINT64 Addr, INT32 Value);
VOID WriteMMIOS16(UINT64 Addr, INT16 Value);
VOID WriteMMIOS8(UINT64 Addr, INT8 Value);

UINT64 ReadMMIOU64(UINT64 Addr);
UINT32 ReadMMIOU32(UINT64 Addr);
UINT16 ReadMMIOU16(UINT64 Addr);
UINT8  ReadMMIOU8(UINT64 Addr);

INT64 ReadMMIOS64(UINT64 Addr);
INT32 ReadMMIOS32(UINT64 Addr);
INT16 ReadMMIOS16(UINT64 Addr);
INT8  ReadMMIOS8(UINT64 Addr);

#ifdef __cplusplus
}
#endif
/* clang-format: off */

#endif