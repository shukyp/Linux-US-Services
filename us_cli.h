/*---------------------------------------------------------------------------------
 * us_cli.h
 * 
 * Header file that exports services of us_cli.c
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
 
#ifndef __US_CLI_H__

#define __US_CLI_H__

// includes
#include "us_types.h"

// types
typedef struct cli_args
{
	bool 	verbose;
	UINT	mdl_num;
} CLI_ARGS;

// prototypes
int cli_parse (int argc, char** argv, CLI_ARGS* cli_args);


#endif // __US_CLI_H__
