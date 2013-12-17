/*	Manually created config.h for Darwin. */

#if defined(__APPLE__) && defined(__MACH__) && !defined(MACOSX)
# define MACOSX
#endif

#ifndef MACOSX
# error "This file is only supported on OS X or iOS."
#endif

#if defined(__i386__)
#define   SYSTEM_BYTEORDER 1
#define   SIZEOF_FLOAT      4
#define   SIZEOF_DOUBLE     8
#define   SIZEOF_LONGDOUBLE 16
#elif defined(__x86_64__)
#define   SYSTEM_BYTEORDER 1
#define   SIZEOF_FLOAT      4
#define   SIZEOF_DOUBLE     8
#define   SIZEOF_LONGDOUBLE 16
#elif defined(__arm__)
#define   SYSTEM_BYTEORDER 1
#define   SIZEOF_FLOAT      4
#define   SIZEOF_DOUBLE     8
#define   SIZEOF_LONGDOUBLE 16
#elif defined(__arm64__)
#define   SYSTEM_BYTEORDER 1
#define   SIZEOF_FLOAT      4
#define   SIZEOF_DOUBLE     8
#define   SIZEOF_LONGDOUBLE 16
#else
#error "Unknown Darwin CPU type"
#endif

#define   HAVE_GCC_BYTESWAP_16 1
#define   HAVE_GCC_BYTESWAP_32 1
#define   HAVE_GCC_BYTESWAP_64 1
/* #undef HAVE_GLIBC_BYTESWAP */
/* #undef HAVE_MSC_BYTESWAP */
/* #undef HAVE_MAC_BYTESWAP */
/* #undef HAVE_OPENBSD_BYTESWAP */
#define HAVE_STD_SHARED_PTR 1
/* #undef HAVE_TR1_SHARED_PTR */
/* #undef HAVE_BOOST_SHARED_PTR */
#define HAVE_STD_UNIQUE_PTR 1
/* #undef HAVE_BOOST_SCOPED_PTR */
#define HAVE_STD_ATOMIC
/* #undef HAVE_BOOST_ATOMIC */
/* #undef HAVE_GCC_ATOMIC */
/* #undef HAVE_MAC_ATOMIC */
/* #undef HAVE_WIN_ATOMIC */
/* #undef HAVE_IA64_ATOMIC */
#define   HAVE_SNPRINTF 1
/* #undef HAVE_SPRINTF_S */
/* #undef HAVE_ISO_STRDUP */
/* #undef HAVE_STD_CODECVT */
#define   HAVE_ZLIB 1
/* #undef TRACE_IN_RELEASE */
