/*---------------------------------------------------------------------------------
 * us_modules.h
 * 
 * Header file that exports services of us_modules.c
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
 * 
 *** Author: Shuky Persky
 *
 * -----------------------------------------------------------------------------------*/
 
#ifndef __US_MODULES_H__

#define __US_MODULES_H__

// includes
#include "us_types.h"

// types

 
// prototypes
UINT get_num_of_us_modules(void); 

const char* const get_us_module_topics(UINT us_mdl_num);

int call_module (UINT us_mdl_num, bool verbose);

void show_us_modules (void);




#endif // __US_MODULES_H__
