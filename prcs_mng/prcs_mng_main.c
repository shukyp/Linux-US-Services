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
#include <stdio.h>

#include "prcs_mng_inner.h"

// extern objects

// defines
#define PAGE_SIZE  (1<<PAGE_SHIFT)

// types

// local objects 

// protoypes


/*------------------------------------------------------------
function: 
	shows the system features 
	
description:	
	calls the appropriate system APIs to get info abot system features.
	then the info is presented in a readable manner.

input:
	None

returns:
	None
  ------------------------------------------------------------*/

#include "us_types.h"

 
int prcs_manage_main(bool verbose)
{
	printf("\n\n prcs_manage_main is running\n\n");
	return 0;
}
