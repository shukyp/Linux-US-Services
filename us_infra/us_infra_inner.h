/*---------------------------------------------------------------------------------
 * us_infra_inner.h
 * 
 * Header file that exports inside the us_infra module
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
#include "us_infra.h"

// types
typedef struct cli_args
{
	bool 	verbose;
	UINT	mdl_num;
} CLI_ARGS;

// prototypes

// us_cli.c
int cli_parse (int argc, char** argv, CLI_ARGS* cli_args);

// us_module.c
UINT get_num_of_us_modules(void);
int call_module (UINT us_mdl_num, bool verbose);
const char* const get_us_module_topics(UINT us_mdl_num);
void show_us_modules (void);

// us_sys_ftr.c
void show_us_sys_features(void);



#endif // __PRCS_MNG_INNER_H__



