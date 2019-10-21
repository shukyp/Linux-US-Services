/*---------------------------------------------------------------------------------
 * us_sys_ftr.c
 * 
 * The module processes the command line and informs the main entry module
 * some results.
 *
 * Header file(s):
 * 	- us_sys_ftr.h
 * 
 * 
 * 
 * Evolution table:
 * 
 * Version	Date			Action
 * ---------------------------------------------------------------------------------
 * 		1	Oct. 15, 2019	Created
 * 
 * 
 *
 *
 * 
 *** Author: Shuky Persky
 *
 * -----------------------------------------------------------------------------------*/

// includes
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#include <sys/utsname.h>

#include "us_infra_inner.h"

// extern objects

// defines
#define PAGE_SIZE  (1<<PAGE_SHIFT)

// types

// local objects 

// protoypes


/*------------------------------------------------------------
description:
	shows the system features
	
	calls the appropriate system APIs to get info abot system features.
	then the info is presented in a readable manner.

input:
	None

returns:
	None
  ------------------------------------------------------------*/
void show_us_sys_features(void)
{
	int 				sys_val;
	struct utsname sys_info;


	// get / present all system run-time capabilities
	sys_val = uname(&sys_info);
	if (sys_val != 0)
	{
		printf ("Call to uname failed - %s... ", strerror(errno));
		exit (EXIT_FAILURE);
	}
	 
	printf("\n\n Basic System Information");
	printf("\n ---------------------------\n");	

	printf ("\nOS name:\t- %s", sys_info.sysname);
	printf ("\nOS releae:\t- %s", sys_info.release);
	printf ("\nOS version:\t- %s", sys_info.version);
	printf ("\nOS machine:\t- %s", sys_info.machine);
	printf ("\nOS nodename:\t- %s", sys_info.nodename);

	printf ("\n\n                ****************\n\n");
 

	// get / present System Features (POSIX 1 based) 
	printf("\n\n System Features (POSIX 1 based)");
	printf("\n ----------------------------------\n");
	
	// ARG_MAX - _SC_ARG_MAX
   //  maximum length of the arguments to the exec, Must not be less than _POSIX_ARG_MAX (4096).
	sys_val = sysconf(_SC_ARG_MAX);
	printf ("\n Maximum length of the arguments: %d (should be >= %d)", sys_val, _POSIX_ARG_MAX);

	// CHILD_MAX - _SC_CHILD_MAX
   // The maximum number of simultaneous processes per user ID., Must not be less than _POSIX_CHILD_MAX (25).
	sys_val = sysconf(_SC_CHILD_MAX);
	printf ("\n Maximum maximum number of simultaneous processes per user ID: %d (should be >= %d)", sys_val, _POSIX_CHILD_MAX);

	// HOST_NAME_MAX - _SC_HOST_NAME_MAX
   // Maximum  length  of a hostname, Must not be less than _POSIX_HOST_NAME_MAX (255).
	sys_val = sysconf(_SC_HOST_NAME_MAX);
	printf ("\n Maximum length of a hostname: %d (should be >= %d)", sys_val, _POSIX_HOST_NAME_MAX);

   // LOGIN_NAME_MAX - _SC_LOGIN_NAME_MAX
   // Maximum length of a login name, Must not be less than _POSIX_LOGIN_NAME_MAX (9).
	sys_val = sysconf(_SC_LOGIN_NAME_MAX);
	printf ("\n Maximum length of a login name: %d (should be >= %d)", sys_val, _POSIX_LOGIN_NAME_MAX);

   // clock ticks - _SC_CLK_TCK
   // The number of clock ticks per second.  The corresponding variable is obsolete.  It was of course called CLK_TCK.
   // (Note: the macro CLOCKS_PER_SEC does not give information: it must equal 1000000.)
	sys_val = sysconf(_SC_CLK_TCK);
	printf ("\n The number of clock ticks per second: %d (enforced be %d)", sys_val, (int)CLOCKS_PER_SEC);

   // NGROUPS_MAX - _SC_NGROUPS_MAX
   // Maximum number of supplementary group IDs.
	sys_val = sysconf(_SC_NGROUPS_MAX);
	printf ("\n The Maximum number of supplementary group IDs: %d", sys_val);

   // OPEN_MAX - _SC_OPEN_MAX
   // The maximum number of files that a process can have open at any time.  Must not be less than _POSIX_OPEN_MAX (20).
	sys_val = sysconf(_SC_OPEN_MAX);
	printf ("\n The maximum # of files a process can have open at any time: %d (should be >= %d)", sys_val, _POSIX_OPEN_MAX);

   // PAGESIZE - _SC_PAGESIZE
   // Size of a page in bytes.  Must not be less than 1.  (Some systems use PAGE_SIZE instead.)
	sys_val = sysconf(_SC_PAGESIZE);
	printf ("\n Size of a page in bytes: %d (should be >= %d)", sys_val, 1);
    
   // RE_DUP_MAX - _SC_RE_DUP_MAX
   // The  number  of  repeated  occurrences  of a BRE permitted by regexec(3) and regcomp(3).
   // Must not be less than _POSIX2_RE_DUP_MAX(255).
	sys_val = sysconf(_SC_RE_DUP_MAX);
	printf ("\n The  number  of  repeated  occurrences  of a BRE permitted by regexec: %d (should be >= %d)", sys_val, _POSIX2_RE_DUP_MAX);

   // STREAM_MAX - _SC_STREAM_MAX
   // The maximum number of streams that a process can have open at any time.
   // If defined, it has the same value as the standard C macro FOPEN_MAX.
   // Must not be less than _POSIX_STREAM_MAX (8).
	sys_val = sysconf(_SC_STREAM_MAX);
	printf ("\n The maximum number of streams that a process can have open at any time: %d (should be >= %d)", sys_val, _POSIX_STREAM_MAX);

   // SYMLOOP_MAX - _SC_SYMLOOP_MAX
   // The maximum number of symbolic links seen in a pathname before resolution returns ELOOP.
   // Must not be less than _POSIX_SYMLOOP_MAX(8).
	sys_val = sysconf(_SC_SYMLOOP_MAX);
	printf ("\n The maximum number of symbolic links seen in a pathname before resolution returns ELOOP: %d (should be >= %d)", sys_val, _POSIX_SYMLOOP_MAX);

   // TTY_NAME_MAX - _SC_TTY_NAME_MAX
   // The maximum length of terminal device name, including the terminating null byte.
   // Must not be less than _POSIX_TTY_NAME_MAX (9).
	sys_val = sysconf(_SC_TTY_NAME_MAX);
	printf ("\n The maximum length of terminal device name: %d (should be >= %d)", sys_val, _POSIX_TTY_NAME_MAX);

   // TZNAME_MAX - _SC_TZNAME_MAX
   // The maximum number of bytes in a timezone name.  Must not be less than _POSIX_TZNAME_MAX (6).
	sys_val = sysconf(_SC_TZNAME_MAX);
	printf ("\n The maximum number of bytes in a timezone name: %d (should be >= %d)", sys_val, _POSIX_TZNAME_MAX);

   // _POSIX_VERSION - _SC_VERSION
   // indicates the year and month the POSIX.1 standard was approved in the format YYYYMML;
   // the value 199009L indicates the  Sept.  1990 revision.
	sys_val = sysconf(_SC_VERSION);
	printf ("\n indicates the year and month the POSIX.1 standard: %d (%s)", sys_val, "199009 indicates the  Sept.  1990 revision");
	
	printf ("\n\n Comment: Some values may be huge and are not suitable for allocating memory ");
	printf ("\n\n                         ****************\n\n");

}

