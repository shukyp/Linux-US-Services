/*---------------------------------------------------------------------------------
 * prcs_mng_inner.h
 * 
 * Header file that exports inside the US_INFRA module prcs_mng module
 *  
 *  
 * 
 * Evolution table:
 * 
 * Version	Date				Action
 * ---------------------------------------------------------------------------------
 * 		1	Oct. 15, 2019	Created
 * 
 * 
 *
 * 
 *** Author: Shuky Persky
 *
 * -----------------------------------------------------------------------------------*/
 
#ifndef __PRCS_MNG_INNER_H__

#define __PRCS_MNG_INNER_H__

// includes
#include "prcs_mng.h"

// types

// prototypes

// prcs_info.c
void display_process_info(void);

// prcs_rsrc.c
void display_process_resource_usage_and_limits(void);

// prcs_create_single_child_using_fork.c
void prcs_create_single_child_using_fork (void);


#endif // __PRCS_MNG_INNER_H__



