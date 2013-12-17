/*	src/config.h. Manually created for Darwin. */

#define COMPILER_IS_GCC 1

#if defined(__APPLE__) && defined(__MACH__) && !defined(MACOSX)
# define MACOSX
#endif

#ifndef MACOSX
# error "This file is only supported on OS X or iOS."
#endif

#define OS_IS_MACOSX 1
#define OS_IS_WIN32 0

#if __BIG_ENDIAN__
# define CPU_IS_BIG_ENDIAN 1
# define WORDS_BIGENDIAN 1
#else
# define CPU_IS_BIG_ENDIAN 0
# define WORDS_BIGENDIAN 0
#endif

#if __LITTLE_ENDIAN__
# define CPU_IS_LITTLE_ENDIAN 1
#else
# define CPU_IS_LITTLE_ENDIAN 0
#endif

#if defined(__i386__)
#define CPU_CLIPS_NEGATIVE 1
#define CPU_CLIPS_POSITIVE 1
#define SF_COUNT_MAX 0x7FFFFFFFFFFFFFFFLL
#define SIZEOF_DOUBLE 8
#define SIZEOF_FLOAT 4
#define SIZEOF_INT 4
#define SIZEOF_INT64_T 8
/* #undef SIZEOF_LOFF_T */
#define SIZEOF_LONG 4
#define SIZEOF_LONG_LONG 8
/* #undef SIZEOF_OFF64_T */
#define SIZEOF_OFF_T 8
#define SIZEOF_SF_COUNT_T 8
#define SIZEOF_SHORT 2
#define SIZEOF_SIZE_T 4
#define SIZEOF_SSIZE_T 4
#define SIZEOF_VOIDP 4
#define SIZEOF_WCHAR_T 4
#define TYPEOF_SF_COUNT_T int64_t
#elif defined(__x86_64__)
#define CPU_CLIPS_NEGATIVE 0
#define CPU_CLIPS_POSITIVE 0
#define SF_COUNT_MAX 0x7FFFFFFFFFFFFFFFLL
#define SIZEOF_DOUBLE 8
#define SIZEOF_FLOAT 4
#define SIZEOF_INT 4
#define SIZEOF_INT64_T 8
/* #undef SIZEOF_LOFF_T */
# define SIZEOF_LONG 8
#define SIZEOF_LONG_LONG 8
#define SIZEOF_OFF_T 8
#define SIZEOF_SF_COUNT_T 8
#define SIZEOF_SHORT 2
#define SIZEOF_SIZE_T 8
#define SIZEOF_SSIZE_T 8
#define SIZEOF_VOIDP 8
#define SIZEOF_WCHAR_T 4
#define TYPEOF_SF_COUNT_T int64_t
#elif defined(__arm__)
#define CPU_CLIPS_NEGATIVE 0
#define CPU_CLIPS_POSITIVE 0
#define SF_COUNT_MAX 0x7FFFFFFFFFFFFFFFLL
#define SIZEOF_DOUBLE 8
#define SIZEOF_FLOAT 4
#define SIZEOF_INT 4
#define SIZEOF_INT64_T 8
/* #undef SIZEOF_LOFF_T */
# define SIZEOF_LONG 4
#define SIZEOF_LONG_LONG 8
/* #undef SIZEOF_OFF64_T */
#define SIZEOF_OFF_T 8
#define SIZEOF_SF_COUNT_T 8
#define SIZEOF_SHORT 2
#define SIZEOF_SIZE_T 4
#define SIZEOF_SSIZE_T 4
#define SIZEOF_VOIDP 4
#define SIZEOF_WCHAR_T 4
#define TYPEOF_SF_COUNT_T int64_t
#elif defined(__arm64__)
#define CPU_CLIPS_NEGATIVE 0
#define CPU_CLIPS_POSITIVE 0
#define SF_COUNT_MAX 0x7FFFFFFFFFFFFFFFLL
#define SIZEOF_DOUBLE 8
#define SIZEOF_FLOAT 4
#define SIZEOF_INT 4
#define SIZEOF_INT64_T 8
/* #undef SIZEOF_LOFF_T */
#define SIZEOF_LONG 8
#define SIZEOF_LONG_LONG 8
#define SIZEOF_OFF_T 8
#define SIZEOF_SF_COUNT_T 8
#define SIZEOF_SHORT 2
#define SIZEOF_SIZE_T 8
#define SIZEOF_SSIZE_T 8
#define SIZEOF_VOIDP 8
#define SIZEOF_WCHAR_T 4
#define TYPEOF_SF_COUNT_T int64_t
#else
# error "Unknown Darwin CPU type"
#endif

#define ENABLE_EXPERIMENTAL_CODE 0
/* #undef HAVE_ALSA_ASOUNDLIB_H */
/* #undef HAVE_BYTESWAP_H */
#define HAVE_CALLOC 1
#define HAVE_CEIL 1
#define HAVE_DECL_S_IRGRP 1
#define HAVE_DLFCN_H 1
/* #undef HAVE_ENDIAN_H */
#define HAVE_EXTERNAL_LIBS 1
#define HAVE_FLEXIBLE_ARRAY 1
#define HAVE_FLOOR 1
#define HAVE_FMOD 1
#define HAVE_FREE 1
#define HAVE_FSTAT 1
#define HAVE_FSYNC 1
#define HAVE_FTRUNCATE 1
#define HAVE_GETPAGESIZE 1
#define HAVE_GETTIMEOFDAY 1
#define HAVE_GMTIME 1
#define HAVE_GMTIME_R 1
#define HAVE_INTTYPES_H 1
#define HAVE_LIBM 1
#define HAVE_LOCALE_H 1
#define HAVE_LOCALTIME 1
#define HAVE_LOCALTIME_R 1
#define HAVE_LRINT 1
#define HAVE_LRINTF 1
#define HAVE_LSEEK 1
#define HAVE_MALLOC 1
#define HAVE_MEMORY_H 1
#define HAVE_MMAP 1
#define HAVE_OPEN 1
#define HAVE_PIPE 1
#define HAVE_PREAD 1
#define HAVE_PWRITE 1
#define HAVE_READ 1
#define HAVE_REALLOC 1
#define HAVE_SETLOCALE 1
/* #undef HAVE_SNDIO_H */
#define HAVE_SNPRINTF 1
#define HAVE_SQLITE3 1
#define HAVE_SSIZE_T 1
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TIME_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_WAIT_H 1
#define HAVE_UNISTD_H 1
#define HAVE_VSNPRINTF 1
#define HAVE_WAITPID 1
#define HAVE_WRITE 1
/* #undef NO_MINUS_C_MINUS_O */

#define PACKAGE "libsndfile"
#define PACKAGE_BUGREPORT "sndfile@mega-nerd.com"
#define PACKAGE_NAME "libsndfile"
#define PACKAGE_STRING "libsndfile 1.0.25"
#define PACKAGE_TARNAME "libsndfile"
#define PACKAGE_URL "http://www.mega-nerd.com/libsndfile/"
#define PACKAGE_VERSION "1.0.25"

#define STDC_HEADERS 1
#define TYPEOF_SF_COUNT_T int64_t

#define USE_WINDOWS_API 0
#define WIN32_TARGET_DLL 0

#define VERSION "1.0.25"

/* #undef _FILE_OFFSET_BITS */
/* #undef _LARGEFILE_SOURCE */
/* #undef _LARGE_FILES */
/* #undef __USE_MINGW_ANSI_STDIO */
