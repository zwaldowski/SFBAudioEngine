/*	Manually created config.h for Darwin. */

#if defined(__APPLE__) && defined(__MACH__) && !defined(MACOSX)
# define MACOSX
#endif

#ifndef MACOSX
# error "This file is only supported on OS X or iOS."
#endif

#ifndef FLAC_CONFIG_H
#define FLAC_CONFIG_H

#include <sys/types.h>
#include <sys/sysctl.h>

#if defined(__i386__)
#define CPU_IS_BIG_ENDIAN 0
#define CPU_IS_LITTLE_ENDIAN 1
#define FLAC__ALIGN_MALLOC_DATA 1
#define FLAC__CPU_IA32 1
#define SIZEOF_OFF_T 8
#define SIZEOF_VOIDP 4
#define WORDS_BIGENDIAN 0
#elif defined(__x86_64__)
#define CPU_IS_BIG_ENDIAN 0
#define CPU_IS_LITTLE_ENDIAN 1
#undef FLAC__ALIGN_MALLOC_DATA
#undef FLAC__CPU_IA32
#define SIZEOF_OFF_T 8
#define SIZEOF_VOIDP 8
#define WORDS_BIGENDIAN 0
#elif defined(__arm__)
#define CPU_IS_BIG_ENDIAN 0
#define CPU_IS_LITTLE_ENDIAN 1
#undef FLAC__ALIGN_MALLOC_DATA
#undef FLAC__CPU_IA32
#define SIZEOF_OFF_T 8
#define SIZEOF_VOIDP 4
#define WORDS_BIGENDIAN 0
#elif defined(__arm64__)
#define CPU_IS_BIG_ENDIAN 0
#define CPU_IS_LITTLE_ENDIAN 1
#undef FLAC__ALIGN_MALLOC_DATA
#undef FLAC__CPU_IA32
#define SIZEOF_OFF_T 8
#define SIZEOF_VOIDP 8
#define WORDS_BIGENDIAN 0
#else
#error "Unknown Darwin CPU type"
#endif

#define AC_APPLE_UNIVERSAL_BUILD 1
/* #undef FLAC__ALIGN_MALLOC_DATA */
/* #undef FLAC__CPU_PPC */
/* #undef FLAC__CPU_PPC_SPE */
/* #undef FLAC__CPU_SPARC */
/* #undef FLAC__HAS_AS */
/* #undef FLAC__HAS_DOCBOOK_TO_MAN */
#define FLAC__HAS_GAS 1
/* FLAC__HAS_NASM */
#define FLAC__HAS_OGG 1
#define FLAC__NO_ASM 1
/* #undef FLAC__SSE_OS */
#define FLAC__SYS_DARWIN 1
/* #undef FLAC__SYS_LINUX */
/* #undef FLAC__USE_3DNOW */
/* #undef FLAC__USE_ALTIVEC */
/* #undef GWINSZ_IN_SYS_IOCTL */
#define HAVE_BSWAP32 1
/* #undef HAVE_BYTESWAP_H */
#define HAVE_CXX_VARARRAYS 1
#define HAVE_C_VARARRAYS 1
#define HAVE_DLFCN_H 1
#define HAVE_FSEEKO 1
#define HAVE_GETOPT_LONG 1
#define HAVE_ICONV 1
#define HAVE_INTTYPES_H 1
#define HAVE_LANGINFO_CODESET 1
#define HAVE_LROUND 1
#define HAVE_MEMORY_H 1
/* #undef HAVE_SOCKLEN_T */
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
#define HAVE_SYS_PARAM_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_TERMIOS_H 1
#define HAVE_TYPEOF 1
#define HAVE_UNISTD_H 1
#define ICONV_CONST 

#define PACKAGE "flac"
#define PACKAGE_BUGREPORT "flac-dev@xiph.org"
#define PACKAGE_NAME "flac"
#define PACKAGE_STRING "flac 1.3.0"
#define PACKAGE_TARNAME "flac"
#define PACKAGE_URL "https://www.xiph.org/flac/"
#define PACKAGE_VERSION "1.3.0"
#define VERSION "1.3.0"

#define STDC_HEADERS 1

#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif

#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif

#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif

#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif

#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif

#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* #undef _FILE_OFFSET_BITS */
/* #undef _LARGEFILE_SOURCE */
/* #undef _LARGE_FILES */
/* #undef _MINIX */
/* #undef _POSIX_1_SOURCE */
/* #undef _POSIX_SOURCE */

#ifndef __cplusplus
/* #undef inline */
#endif

/* #undef typeof */

#endif
