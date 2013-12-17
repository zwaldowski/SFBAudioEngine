/*	Manually created config_types.h for Ogg. */

#if defined(__APPLE__) && defined(__MACH__) && !defined(MACOSX)
# define MACOSX
#endif

#ifndef MACOSX
# error "This file is only supported on OS X or iOS."
#endif

#ifndef __CONFIG_TYPES_H__
#define __CONFIG_TYPES_H__

#define INCLUDE_INTTYPES_H 1
#define INCLUDE_STDINT_H 1
#define INCLUDE_SYS_TYPES_H 1

#include <inttypes.h>
#include <stdint.h>
#include <sys/types.h>

typedef int16_t ogg_int16_t;
typedef uint16_t ogg_uint16_t;
typedef int32_t ogg_int32_t;
typedef uint32_t ogg_uint32_t;
typedef int64_t ogg_int64_t;

#endif
