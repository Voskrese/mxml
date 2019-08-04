/* Copyright(c) 2019 Intel Corporation
*/

#ifndef _UNISTD_H
#define _UNISTD_H    1

/**
 * This file is added to support common code in eal_common_lcore.c
 * as Microsoft libc does not contain unistd.h. This may be removed
 * in future releases.
 */

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN  /* We always want minimal includes */
#endif
#endif

/* Windows only have little endian architecture. */
#if defined(WIN32) || defined(_WIN32)
#define OS_WINDOWS 1
#define USE_SYSTEM_MALLOC 1
#define PLATFORM_WIN 1
#define CPU_LITTLE_ENDIAN 1
#define USE_WINDOWS_EVENT_LOOP 1
#endif

#ifdef HAVE_SYS_TYPES_H
#	include <sys/types.h>
#endif

#ifdef HAVE_PROCESS_H
#	include <process.h>
#endif

#pragma once

#include <io.h>
#include <stdio.h>

#define access _access

#define __builtin_bswap32 _byteswap_ulong
#define __builtin_bswap16 _byteswap_ushort

#ifdef _WIN32
#define sleep _sleep
#define strdup _strdup
#define unlink _unlink
#endif

#define R_OK    04       /* Test for read permission.  */    /* read-only (for access()) */
#define W_OK    02       /* Test for write permission.  */
//#define   X_OK    01   /* execute permission - unsupported in windows*/
#define F_OK    00       /* Test for existence.  */

/* read, write, and close are NOT being #defined here, because while there are file handle specific versions for Windows, they probably don't work for sockets. You need to look at your app and consider whether to call e.g. closesocket(). */
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* defines how to decorate public symbols while building */
#ifdef _MSC_VER
  #if defined(_LIB)
    #define _EXTERN extern
  #else
    #define _EXTERN __declspec(dllexport) extern
  #endif
#else
  #define _EXTERN __attribute__((visibility("default"))) __declspec(dllexport) extern
#endif

#ifndef __cplusplus
/* I don't see how to get inlining for C code in MSVC.  Ah well. */
#define inline
#endif

typedef int mode_t;

#endif /* _UNISTD_H_ */
