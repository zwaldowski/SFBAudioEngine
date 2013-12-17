/*	Manually created config.h for Darwin. */

#if defined(__APPLE__) && defined(__MACH__) && !defined(MACOSX)
# define MACOSX
#endif

#ifndef MACOSX
# error "This file is only supported on OS X or iOS."
#endif

#if defined(__i386__)
# define SIZEOF_INT 4
# define SIZEOF_LONG 4
# define SIZEOF_SHORT 2
# undef WORDS_BIGENDIAN
# define _USE_SSE 
#elif defined(__x86_64__)
# define SIZEOF_INT 4
# define SIZEOF_LONG 8
# define SIZEOF_SHORT 2
# undef WORDS_BIGENDIAN
# define _USE_SSE 
#elif defined(__arm__)
# define SIZEOF_INT 4
# define SIZEOF_LONG 4
# define SIZEOF_SHORT 2
# undef WORDS_BIGENDIAN
# undef _USE_SSE
#elif defined(__arm64__)
# define SIZEOF_INT 4
# define SIZEOF_LONG 8
# define SIZEOF_SHORT 2
# undef WORDS_BIGENDIAN
# undef _USE_SSE
#else
# error "Unknown Darwin CPU type"
#endif

/* #undef ARM4_ASM */
/* #undef ARM5E_ASM */
/* #undef BFIN_ASM */
/* #undef DISABLE_FLOAT_API */
/* #undef DISABLE_VBR */
/* #undef ENABLE_VALGRIND */
#define EXPORT __attribute__((visibility("default")))
/* #undef FIXED_DEBUG */
/* #undef FIXED_POINT */
#define FLOATING_POINT 
#define HAVE_ALLOCA_H 1
#define HAVE_DLFCN_H 1
#define HAVE_GETOPT_H 1
#define HAVE_GETOPT_LONG 1
#define HAVE_INTTYPES_H 1
#define HAVE_LIBM 1
/* #undef HAVE_LIBWINMM */
#define HAVE_MEMORY_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
/* #undef HAVE_SYS_AUDIOIO_H */
/* #undef HAVE_SYS_SOUNDCARD_H */
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_UNISTD_H 1

#define PACKAGE_BUGREPORT ""
#define PACKAGE_NAME ""
#define PACKAGE_STRING ""
#define PACKAGE_TARNAME ""
#define PACKAGE_VERSION ""

#define SPEEX_EXTRA_VERSION ""
#define SPEEX_MAJOR_VERSION 1
#define SPEEX_MICRO_VERSION 16
#define SPEEX_MINOR_VERSION 1
#define SPEEX_VERSION "1.2rc1"

#define STDC_HEADERS 1
/* #undef TI_C55X */
/* #undef USE_ALLOCA */
/* #undef USE_GPL_FFTW3 */
/* #undef USE_INTEL_MKL */
/* #undef USE_KISS_FFT */
#define USE_SMALLFT 
#define VAR_ARRAYS 
/* #undef const */
#ifndef __cplusplus
/* #undef inline */
#endif
/* #undef restrict */
