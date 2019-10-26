/*---------------------------------------------------------------------------------
 * prcs_mng_main.c
 * 
 * The module show the process info
 *
 * Header file(s):
 * 	prcs_mng_inner.h
 * 
 * 
 * 
 * Evolution table:
 * 
 * Version	Date				Action
 * ---------------------------------------------------------------------------------
 * 		1	Oct. 25, 2019	Created
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

 
/*------------------------------------------------------------
function: 
	displays some info about the process  
	
input:	
	none

returns: 
	none
  ------------------------------------------------------------*/
void display_process_info(void)
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

