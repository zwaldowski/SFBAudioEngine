/*	libplatform/config.h. Manually created for Darwin. */

#if defined(__APPLE__) && defined(__MACH__) && !defined(MACOSX)
# define MACOSX
#endif

#ifndef MACOSX
# error "This file is only supported on OS X or iOS."
#endif

#define HAVE_DLFCN_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_MEMORY_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_UNISTD_H 1
#define STDC_HEADERS 1

/* #undef LT_OBJDIR */
/* #undef NEED_LFS_ACTIVATION */

#define PACKAGE "mp4v2"
#define PACKAGE_BUGREPORT "kidjan@gmail.com"
#define PACKAGE_NAME "MP4v2"
#define PACKAGE_STRING "MP4v2 trunk-r504"
#define PACKAGE_URL ""
#define PACKAGE_VERSION "trunk-r504"
#define VERSION "trunk-r504"
