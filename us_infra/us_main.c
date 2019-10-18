/*---------------------------------------------------------------------------------
 * us_main.c
 * 
 * The module is the project entry point. 
 * The module processes the command line options and invokes the us_module of interest 
 * 
 * Header file(s): N/A
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
 
#include "us_infra_inner.h"

// extern objects

// defines

// types
 
// local objects 

// protoypes


/*------------------------------------------------------------
function: 
	Main program entry point 
	
input:	
	argc	- programs CLI options counter
	argv	- programs CLI options string
	
returns: 
	int - exit code (report to OS based process manager)
  ------------------------------------------------------------*/  
int main (int argc, char* argv[])
{
	int		rc;
	int		exit_code;
	char*		program_name;
	CLI_ARGS	cli_args;
	
	// init
	exit_code = 0;
	cli_args.verbose = false;
	cli_args.mdl_num = 0;

	// print welcome message
	program_name = argv[0];
	
	// if no CLI options - displau usage & quit
	if (argc == 1)
	{
		printf("\n\nWelcome to %s, No CLI options. Try calling with -h (Usage advise), Quit ...\n\n", program_name);
		exit(EXIT_SUCCESS);
	}
	
	// being here means there is at least one CLI option
	
	// Welcome message
	printf ("\n\nWelcome to %s, %d CLI option(s) being parsed ... \n\n", program_name, argc-1);

	// parse 
	exit_code = cli_parse (argc, argv, &cli_args);
	if (exit_code != EXIT_SUCCESS)
	{
		printf ("\n\n An error took place while parsing the CLI options (try -h for help), Quit\n\n");
		exit(-EXIT_FAILURE);
	}

	// if a module number provided - call it
	if (cli_args.mdl_num > 0)
	{
		if (cli_args.mdl_num <= get_num_of_us_modules())
		{
			// invoke the requested module
			rc = call_module(cli_args.mdl_num, cli_args.verbose);
			exit (rc);
		}
		else
		{
			// clean up 
			printf("\n\n Invalid module number (try -l option for help), Quit ...\n\n");
			exit (EXIT_SUCCESS);
		}
	}		

	// Quit 
	exit (EXIT_SUCCESS);
}

