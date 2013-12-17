/*	Manually created config.h for Darwin. */

#if defined(__APPLE__) && defined(__MACH__) && !defined(MACOSX)
# define MACOSX
#endif

#ifndef MACOSX
# error "This file is only supported on OS X or iOS."
#endif

# include "TargetConditionals.h"

# if TARGET_IPHONE_SIMULATOR
#  define DEFAULT_OUTPUT_MODULE "dummy"
#  undef DYNAMIC_BUILD
#  undef HAVE_CORESERVICES_CORESERVICES_H
#  undef HAVE_LIBMX
#  undef HAVE_MMAP
#  undef HAVE_OPENAL_ALC_H
#  undef HAVE_OPENAL_AL_H
# elif TARGET_OS_IPHONE
#  define DEFAULT_OUTPUT_MODULE "dummy"
#  undef DYNAMIC_BUILD
#  undef HAVE_CORESERVICES_CORESERVICES_H
#  undef HAVE_LIBMX
#  undef HAVE_MMAP
#  undef HAVE_OPENAL_ALC_H
#  undef HAVE_OPENAL_AL_H
# elif TARGET_OS_MAC
#  define DEFAULT_OUTPUT_MODULE "coreaudio"
#  define DYNAMIC_BUILD 1
#  define HAVE_CORESERVICES_CORESERVICES_H 1
#  define HAVE_LIBMX 1
#  define HAVE_MMAP 1
#  define HAVE_OPENAL_ALC_H 1
#  define HAVE_OPENAL_AL_H 1
# else
#  error "Unknown target."
# endif

#if defined(__i386__)
# define ABI_ALIGN_FUN 1
# define HAVE_GAI_ADDRCONFIG 1
# define IEEE_FLOAT 1
# define SIZEOF_INT32_T 4
# define SIZEOF_LONG 4
# define SIZEOF_OFF_T 8
# define SIZEOF_SIZE_T 4
# define SIZEOF_SSIZE_T 4
# define OPT_I586
# undef WORDS_BIGENDIAN
#elif defined(__x86_64__)
# undef ABI_ALIGN_FUN
# define HAVE_GAI_ADDRCONFIG 1
# define IEEE_FLOAT 1
# define SIZEOF_INT32_T 4
# define SIZEOF_LONG 8
# define SIZEOF_OFF_T 8
# define SIZEOF_SIZE_T 8
# define SIZEOF_SSIZE_T 8
# undef WORDS_BIGENDIAN
# define OPT_X86_64
#elif defined(__arm__)
# undef ABI_ALIGN_FUN
# undef HAVE_GAI_ADDRCONFIG
# undef IEEE_FLOAT
# define SIZEOF_INT32_T 4
# define SIZEOF_LONG 4
# define SIZEOF_OFF_T 8
# define SIZEOF_SIZE_T 4
# define SIZEOF_SSIZE_T 4
# define OPT_NEON
# undef WORDS_BIGENDIAN
#elif defined(__arm64__)
# undef ABI_ALIGN_FUN
# undef HAVE_GAI_ADDRCONFIG
# undef IEEE_FLOAT
# define SIZEOF_INT32_T 4
# define SIZEOF_LONG 8
# define SIZEOF_OFF_T 8
# define SIZEOF_SIZE_T 8
# define SIZEOF_SSIZE_T 8
# undef WORDS_BIGENDIAN
# define OPT_GENERIC
#else
#error "Unknown Darwin CPU type"
#endif

/* #undef ACCURATE_ROUNDING */
#define AC_APPLE_UNIVERSAL_BUILD 1
#define ASMALIGN_BALIGN 1
/* #undef ASMALIGN_BYTE */
/* #undef ASMALIGN_EXP */
#define CCALIGN 1
/* #undef EOVERFLOW */
#define FIFO 1
#define FRAME_INDEX 1
#define GAPLESS 1
/* #undef HAVE_ALC_H */
/* #undef HAVE_ALIB_H */
/* #undef HAVE_AL_ALC_H */
/* #undef HAVE_AL_AL_H */
/* #undef HAVE_AL_H */
#define HAVE_ARPA_INET_H 1
/* #undef HAVE_ASM_AUDIOIO_H */
#define HAVE_ATOLL 1
/* #undef HAVE_AUDIOS_H */
#define HAVE_AUDIOTOOLBOX_AUDIOTOOLBOX_H 1
#define HAVE_AUDIOUNIT_AUDIOUNIT_H 1
/* #undef HAVE_CULIB_H */
#define HAVE_DLFCN_H 1
#define HAVE_GETADDRINFO 1
#define HAVE_GETPAGESIZE 1
#define HAVE_GETUID 1
#define HAVE_INTTYPES_H 1
#define HAVE_LANGINFO_H 1
#define HAVE_LIBM 1
#define HAVE_LIMITS_H 1
/* #undef HAVE_LINUX_SOUNDCARD_H */
#define HAVE_LOCALE_H 1
/* #undef HAVE_LTDL */
/* #undef HAVE_MACHINE_SOUNDCARD_H */
#define HAVE_MEMORY_H 1
#define HAVE_MKFIFO 1
#define HAVE_NETDB_H 1
#define HAVE_NETINET_IN_H 1
/* #undef HAVE_NETINET_TCP_H */
#define HAVE_NL_LANGINFO 1
/* #undef HAVE_OS2ME_H */
/* #undef HAVE_OS2_H */
#define HAVE_RANDOM 1
#define HAVE_SCHED_H 1
/* #undef HAVE_SCHED_SETSCHEDULER */
#define HAVE_SETLOCALE 1
#define HAVE_SETPRIORITY 1
#define HAVE_SETUID 1
#define HAVE_SIGNAL_H 1
/* #undef HAVE_SNDIO_H */
#define HAVE_STDINT_H 1
#define HAVE_STDIO_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRDUP 1
#define HAVE_STRERROR 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
/* #undef HAVE_SUN_AUDIOIO_H */
/* #undef HAVE_SYS_AUDIOIO_H */
/* #undef HAVE_SYS_AUDIO_H */
#define HAVE_SYS_IOCTL_H 1
#define HAVE_SYS_PARAM_H 1
#define HAVE_SYS_RESOURCE_H 1
#define HAVE_SYS_SIGNAL_H 1
#define HAVE_SYS_SOCKET_H 1
/* #undef HAVE_SYS_SOUNDCARD_H */
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TIME_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_WAIT_H 1
#define HAVE_TERMIOS 1
#define HAVE_UNISTD_H 1
/* #undef HAVE_WINDOWS_H */
/* #undef HAVE_WS2TCPIP_H */
#define INDEX_SIZE 1000
#define IPV6 1
#define LFS_ALIAS_BITS 64
#define LT_OBJDIR ".libs/"
#define MODULE_FILE_SUFFIX ".so"
#define NETWORK 1
/* #undef NO_16BIT */
/* #undef NO_32BIT */
/* #undef NO_8BIT */
/* #undef NO_DOWNSAMPLE */
/* #undef NO_ERETURN */
/* #undef NO_ERRORMSG */
/* #undef NO_FEEDER */
/* #undef NO_ICY */
/* #undef NO_ID3V2 */
/* #undef NO_LAYER1 */
/* #undef NO_LAYER2 */
/* #undef NO_LAYER3 */
/* #undef NO_NTOM */
/* #undef NO_REAL */
/* #undef NO_STRING */
/* #undef NO_WARNING */

#define PACKAGE "mpg123"
#define PACKAGE_BUGREPORT "mpg123-devel@lists.sourceforge.net"
#define PACKAGE_NAME "mpg123"
#define PACKAGE_STRING "mpg123 1.16.0"
#define PACKAGE_TARNAME "mpg123"
#define PACKAGE_URL ""
#define PACKAGE_VERSION "1.16.0"
#define VERSION "1.16.0"

/* #undef PORTAUDIO18 */
#define STDC_HEADERS 1
/* #undef USE_MODULES */
#define USE_NEW_HUFFTABLE 1
/* #undef USE_YASM_FOR_AVX */
/* #undef WANT_WIN32_FIFO */
/* #undef WANT_WIN32_SOCKETS */
/* #undef WANT_WIN32_UNICODE */
/* #undef WINVER */

#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* #undef _FILE_OFFSET_BITS */
/* #undef _LARGE_FILES */
/* #undef _WIN32_WINNT */
/* #undef const */
#ifndef __cplusplus
/* #undef inline */
#endif

/* #undef int16_t */
/* #undef int32_t */
#define lfs_alias_t off_t
/* #undef off_t */
/* #undef size_t */
/* #undef ssize_t */
/* #undef uint16_t */
/* #undef uint32_t */
/* #undef uintptr_t */

#define REAL_IS_FLOAT
#define NOXFERMEM
#define NEWOLD_WRITE_SAMPLE
