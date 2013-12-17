/*	Manually created config.h for Darwin. */

#if defined(__APPLE__) && defined(__MACH__) && !defined(MACOSX)
# define MACOSX
#endif

#ifndef MACOSX
# error "This file is only supported on OS X or iOS."
#endif

#define FLOATING_POINT 1
/* #undef CUSTOM_MODES */
/* #undef DISABLE_FLOAT_API */
/* #undef ENABLE_ASSERTIONS */
/* #undef FIXED_DEBUG */
/* #undef FIXED_POINT */
/* #undef FLOAT_APPROX */
/* #undef FUZZING */
/* #undef HAVE_ALLOCA_H */
#define HAVE_DLFCN_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_LRINT 1
#define HAVE_LRINTF 1
#define HAVE_MEMORY_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_UNISTD_H 1
/* #undef HAVE___MALLOC_HOOK */
/* #undef NO_MINUS_C_MINUS_O */
/* #undef OPUS_ARM_ASM */
/* #undef OPUS_ARM_INLINE_ASM */
/* #undef OPUS_ARM_INLINE_EDSP */
/* #undef OPUS_ARM_INLINE_MEDIA */
/* #undef OPUS_ARM_INLINE_NEON */
/* #undef OPUS_ARM_MAY_HAVE_EDSP */
/* #undef OPUS_ARM_MAY_HAVE_MEDIA */
/* #undef OPUS_ARM_MAY_HAVE_NEON */
/* #undef OPUS_ARM_PRESUME_EDSP */
/* #undef OPUS_ARM_PRESUME_MEDIA */
/* #undef OPUS_ARM_PRESUME_NEON */
/* This is a build of OPUS */
#define OPUS_BUILD /**/
/* #undef OPUS_HAVE_RTCD */

#define PACKAGE_BUGREPORT "opus@xiph.org"
#define PACKAGE_NAME "opus"
#define PACKAGE_STRING "opus 1.1"
#define PACKAGE_TARNAME "opus"
#define PACKAGE_URL ""
#define PACKAGE_VERSION "1.1"

#define STDC_HEADERS 1
#define VAR_ARRAYS 1
/* #undef const */

#ifndef __cplusplus
/* #undef inline */
#endif

#define restrict __restrict
#if defined __SUNPRO_CC && !defined __RESTRICT
# define _Restrict
# define __restrict__
#endif
