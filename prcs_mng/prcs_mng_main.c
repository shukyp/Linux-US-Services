/*---------------------------------------------------------------------------------
 * prcs_mng_main.c
 * 
 * The module covers various topics that pertain to creation, management
 *
 * Header file(s):
 * 	prcs_mng.h
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
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

#include <stdio.h>

#include "prcs_mng_inner.h"

// extern objects

// defines

// types

// local objects 

// protoypes
static void display_process_info(void);
static void display_process_resource_usage_and_limits(void);


/*------------------------------------------------------------
function: 
	prcs_mng main entry point 
	
input:	
	verbose - indicates whether verbose mode on enabled

returns: 
	none
  ------------------------------------------------------------*/
int prcs_manage_main(bool verbose)
{
	// advise
	printf("\n\n Module: prcs_manage is running\n\n");
	
	// show some process self-info 
	display_process_info();

	// display limits
	display_process_resource_usage_and_limits();

	// process children management (create, monitr, destroy)
	printf("\n\n >>> To be added soon:  ");
	printf ("\n      process children management (create, monitr, destroy)\n\n");

	// we ar done
	return 0;
}

 
/*------------------------------------------------------------
function: 
	displays some info about the process  
	
input:	
	none

returns: 
	none
  ------------------------------------------------------------*/
static void display_process_info(void)
{
	printf ("\n Process Info");
	printf ("\n --------------");

	printf ("\n Own ID: %d", getpid());
	printf ("\n Parent ID: %d", getppid());

	printf ("\n");
	
	printf ("\n User ID:%d, effective:%d", getuid(), geteuid());

	printf ("\n Primary group ID:%d, Effective:%d", getgid(), getegid());
	printf ("\n Max amount of supplemental groups: %ld", sysconf(_SC_NGROUPS_MAX));

	// get (and display) the amount of supplemental GIDs
	int actualGroups = getgroups(0, 0); // get amount of supplemental GIDs
	printf ("\n Actual amount of supplemental groups: %d (", actualGroups); // show amount of supplemental GIDs

	if (actualGroups > 0)
	{
		// alloc memory to accomodate IDs of supplemental groups
		gid_t* splmntGidArr = malloc(actualGroups * sizeof(gid_t)); // alocate memory to hold supplemental GIDs

		// get & populate with supplemental GIDs
		getgroups(actualGroups, splmntGidArr);

		// shaping teh output
		printf("#: ");
		
		// show supplemental GIDs values
		for (int i=0; i<actualGroups; i++) 
		{
			// show supplemental group ID
			printf("%d", splmntGidArr[i]);

			// if not the last one ...
			if ((actualGroups-i)>1)
				printf(" ");
			else
				printf(") \n");
		}

		// free allocated memory
		free(splmntGidArr);		
	}
		
	printf ("\n Max simultaneous open streams: %ld", sysconf(_SC_STREAM_MAX));
	printf ("\n Max CLI & ENV buffer length (bytes): %ld", sysconf(_SC_ARG_MAX));
	printf ("\n Max simultaneous open files:  %ld", sysconf(_SC_OPEN_MAX));
	printf ("\n Memory allocation Page size: %ld", sysconf(_SC_PAGE_SIZE));

	printf ("\n \n\n\t\t ****************** \n\n\n");

}


/*------------------------------------------------------------
function: 
	displays some info about the process  
	
input:	
	none

returns: 
	none
  ------------------------------------------------------------*/
static void display_process_resource_usage_and_limits(void)
{
	float		user_duration;
	float		krnl_duration;
	struct 	rusage	usage_info;
	struct 	rlimit 	limit_info;
	
	printf("\n\n Process Resource Usage Info of the Process");
	printf("\n -------------------------------------------------");

	// get usage info
	getrusage(RUSAGE_SELF, &usage_info);

	// show time consumption for the process
	user_duration = (float)usage_info.ru_utime.tv_sec + (float)usage_info.ru_utime.tv_usec/1000000;
	krnl_duration = (float)usage_info.ru_stime.tv_sec + (float)usage_info.ru_stime.tv_usec/1000000;
	printf("\n Duration: User-Space:%.05f Secs, Kernel-Space:%.05f Secs", user_duration, krnl_duration);

	// memory allocation event by kernel w/o accessing the swap file
	printf("\n More Memory allocation events (no access to swap file): %ld", usage_info.ru_minflt); 
	printf("\n Memory page-fault events(requires access to swap file): %ld", usage_info.ru_majflt);
	printf("\n #of pages loaded from swap due to memory page-fault : %ld", usage_info.ru_nswap);


	printf("\n\n Process Resource Usage Info of the Process's Children");
	printf("\n --------------------------------------------------------");

	// get usage info
	getrusage(RUSAGE_CHILDREN, &usage_info);

	// show time consumption for the process
	user_duration = (float)usage_info.ru_utime.tv_sec + (float)usage_info.ru_utime.tv_usec/1000000;
	krnl_duration = (float)usage_info.ru_stime.tv_sec + (float)usage_info.ru_stime.tv_usec/1000000;
	printf("\n Duration: User-Space:%.05f Secs, Kernel-Space:%.05f Secs", user_duration, krnl_duration);

	// other events that has to with memory consumption/management
	printf("\n More Memory allocation events (no access to swap file): %ld", usage_info.ru_minflt); 
	printf("\n Memory page-fault events(requires access to swap file): %ld", usage_info.ru_majflt);
	printf("\n #of pages loaded from swap due to memory page-fault : %ld", usage_info.ru_nswap);
		
	printf ("\n \n\n\t\t ****************** \n\n\n");	
	
	printf("\n\n Process Resource Limits Info");
	printf("\n --------------------------------");
	
	printf("\n Hard Limits: set by the Linux distro / -1: no limit");
	printf("\n Soft Limits: set by the Linux Kernel / -1: no limit (can't exceed Hard limits)");
	
	// get max amount of memory available for the process
	getrlimit(RLIMIT_AS, &limit_info);
	printf("\n\n Max memory size available to the process(Data, BSS, Stack, Heap)");
	printf("\n Hard Limit: %ld", limit_info.rlim_max);
	printf("\n Soft Limit: %ld", limit_info.rlim_cur);

	// get max amount of memory footprint available for the process
	getrlimit(RLIMIT_RSS, &limit_info);
	printf("\n\n Max memory footprint of the process(Data, BSS, Stack, Heap)");
	printf("\n Exceeding this value will trigger pageout of process resources");
	printf("\n Hard Limit: %ld", limit_info.rlim_max);
	printf("\n Soft Limit: %ld", limit_info.rlim_cur);

	// get max size of core dump file
	getrlimit(RLIMIT_RSS, &limit_info);
	printf("\n\n Max size of core dump file");
	printf("\n Hard Limit: %ld", limit_info.rlim_max);
	printf("\n Soft Limit: %ld", limit_info.rlim_cur);
	
	// show CPU time consumption for the process
	getrlimit(RLIMIT_CPU, &limit_info);
	printf("\n\n Max CPU time");
	printf("\n Hard Limit: %ld", limit_info.rlim_max);
	printf("\n Soft Limit: %ld", limit_info.rlim_cur);
	
	// show max memory size for Data/BSS 
	getrlimit(RLIMIT_DATA, &limit_info);
	printf("\n\n Max memory size for Data/BSS");
	printf("\n Hard Limit: %ld", limit_info.rlim_max);
	printf("\n Soft Limit: %ld", limit_info.rlim_cur);
		
	// show max writing to files 
	getrlimit(RLIMIT_FSIZE, &limit_info);
	printf("\n\n Max writing to files");
	printf("\n Hard Limit: %ld", limit_info.rlim_max);
	printf("\n Soft Limit: %ld", limit_info.rlim_cur);
		
	// show max memory that can be blocked 
	getrlimit(RLIMIT_MEMLOCK, &limit_info);
	printf("\n\n Max memory that can be locked");
	printf("\n Hard Limit: %ld", limit_info.rlim_max);
	printf("\n Soft Limit: %ld", limit_info.rlim_cur);
		
	// show max number of concurrent open files
	getrlimit(RLIMIT_NOFILE, &limit_info);
	printf("\n\n Max number of concurrent open files");
	printf("\n Hard Limit: %ld", limit_info.rlim_max);
	printf("\n Soft Limit: %ld", limit_info.rlim_cur);
		
	// show max number of concurrent direct children
	getrlimit(RLIMIT_NPROC, &limit_info);
	printf("\n\n Max number of concurrent direct children");
	printf("\n Hard Limit: %ld", limit_info.rlim_max);
	printf("\n Soft Limit: %ld", limit_info.rlim_cur);
		
	// show max used RAM at any given time (exceeding triggers page-out)
	getrlimit(RLIMIT_RSS, &limit_info);
	printf("\n\n Max used RAM at any given time (exceeding triggers page-out)");
	printf("\n Hard Limit: %ld", limit_info.rlim_max);
	printf("\n Soft Limit: %ld", limit_info.rlim_cur);

		
	// show max size of stack memroy
	getrlimit(RLIMIT_STACK, &limit_info);
	printf("\n\n Max size of stack memroy");
	printf("\n Hard Limit: %ld", limit_info.rlim_max);
	printf("\n Soft Limit: %ld", limit_info.rlim_cur);
		
	printf ("\n \n\n\t\t ****************** \n\n\n");
}
