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
//extern char* environ[]; // POSIX defined - not supported by ubuntu

// defines

// types
 
// local objects 

// protoypes
static void show_cli_args(int argc, char** argv);
static void show_environ_vars(char* environ[]);


/*------------------------------------------------------------
function: 
	Main program entry point 
	
input:	
	argc	- programs CLI options counter
	argv	- programs CLI options string
	
returns: 
	int - exit code (report to OS based process manager)
  ------------------------------------------------------------*/  
int main (int argc, char* argv[], char* environ[])
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
		exit(EXIT_FAILURE);
	}

	// if verbose mode - display CLI options and environment variables
	if (cli_args.verbose)
	{		
		show_cli_args(argc, argv);
		show_environ_vars (environ);
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


/*------------------------------------------------------------
function: 
	displays the actual CLI arguments  
	
description:	
	displays the actual CLI arguments one at a line

input:
	argc	- programs CLI options counter
	argv	- programs CLI options array of string pointers

returns: 
	None
  ------------------------------------------------------------*/
static void	show_cli_args(int argc, char** argv)
{
	printf ("\n\n CLI arguments");
	printf ("\n ---------------");
	
	for (int i=1; i<argc; ++i)
		printf ("\n Argument# %d: %s", i, argv[i]);

	printf ("\n\n");
}


/*------------------------------------------------------------
function: 
	displays the actual environment variables  
	
description:	
	ddisplays the actual environment variables one at a line

input:
	environ	- programs environment variables array of string pointers

returns: 
	None
  ------------------------------------------------------------*/
static void show_environ_vars(char* environ[])
{
	char* var_val;
	char* orgnl_val;
	int	env_len;
	
	printf ("\n\n Environment Variables");
	printf ("\n -------------------------");

	// traverse thru all environment variables
	for (env_len=0; (environ[env_len] != NULL); env_len++);

	// show length of environment and each entry's NAME=VALUE
	printf("\n The number of environment variables: %d\n", env_len);

	for (int i=0; i<env_len; i++)
		printf("\n [%02d] %s", i+1, environ[i]);
	
	printf ("\n\n");
	
	// Fetch content of specifc env. variables
	printf("\n Fetching Values of 'USER' and 'HOME' variabled");
	printf("\n USER: %s", (((var_val = getenv("USER")) != (char*)NULL)? var_val : "N/A"));
	printf("\n HOME: %s", (((var_val = getenv("HOME")) != (char*)NULL)? var_val : "N/A"));

	// overwrite values of an existing variable and display
	orgnl_val = getenv("USER"); // keep original value aside
	printf("\n\n\n Set 'User' to to different value and then fetch and display it");
	putenv("USER=Trump"); // POSIX defined. overrides if variable exists
	printf("\n USER: %s (changed)", (((var_val = getenv("USER")) != (char*)NULL)? var_val : "N/A"));
	setenv("USER", orgnl_val, 1); // 1-means overwrite if exist
	printf("\n USER: %s (recovered)", (((var_val = getenv("USER")) != (char*)NULL)? var_val : "N/A"));

	printf ("\n\n");
}

