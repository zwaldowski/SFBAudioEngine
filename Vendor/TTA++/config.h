/*	Manually created config.h for Darwin. */

#if defined(__APPLE__) && defined(__MACH__) && !defined(MACOSX)
# define MACOSX
#endif

#ifndef MACOSX
# error "This file is only supported on OS X or iOS."
#endif

#if defined(__i386__)
#undef CPU_ARM
#define CPU_X86
#ifdef __SSE2__
#define ENABLE_SSE2
#else
#undef ENABLE_SSE2
#endif
#ifdef __SSE4__
#define ENABLE_SSE4
#else
#undef ENABLE_SSE4
#endif
#elif defined(__x86_64__)
#undef CPU_ARM
#define CPU_X86
#ifdef __SSE2__
#define ENABLE_SSE2
#else
#undef ENABLE_SSE2
#endif
#ifdef __SSE4__
#define ENABLE_SSE4
#else
#undef ENABLE_SSE4
#endif
#elif defined(__arm__)
#define CPU_ARM
#undef CPU_X86
#undef ENABLE_SSE2
#undef ENABLE_SSE4
#elif defined(__arm64__)
#undef CPU_ARM
#undef ENABLE_SSE2
#undef ENABLE_SSE4
#else
#error "Unknown Darwin CPU type"
#endif

/* #undef CPU_MIPS */
/* #undef ENABLE_ASM */
/* #undef ENABLE_FRW */
/* #undef HAVE_LSEEK64 */
#define HAVE_MALLOC 1
#define HAVE_MEMCPY 1
#define HAVE_MEMSET 1
#define HAVE_READ 1
#define HAVE_WRITE 1
#define PACKAGE "libtta++"
#define PACKAGE_BUGREPORT "info@true-audio.com"
#define PACKAGE_NAME "libtta++"
#define PACKAGE_STRING "libtta++ 2.1"
#define PACKAGE_VERSION "2.1"
#define STDC_HEADERS 1
#define VERSION "2.1"
/* #undef _FILE_OFFSET_BITS */
/* #undef _LARGE_FILES */
