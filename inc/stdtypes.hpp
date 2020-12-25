/* TODO: Consider removing dependency on stdint since it isn't guaranteed
 * to be present under ISO 9899 */
#include <stdint.h>

#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

/* clang-format: off */
#ifdef __cplusplus
extern "C"
{
#endif

typedef uint64_t UINT64;
typedef uint32_t UINT32;
typedef uint16_t UINT16;
typedef uint8_t UINT8;

typedef int64_t INT64;
typedef int32_t INT32;
typedef int16_t INT16;
typedef int8_t INT8;

typedef void VOID;
typedef void *VOIDPTR;

typedef UINT8 BOOL;

#ifndef NULL
#define NULL ((void*)(0))
#endif

#ifndef NULLPTR
#define NULLPTR NULL
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifdef __cplusplus
}
#endif
/* clang-format: off */

#endif