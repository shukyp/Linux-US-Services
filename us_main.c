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
#include <getopt.h>

#include "us_types.h"

#include "us_cli.h"

// extern objects
extern char *optarg;	// argument value of the option	(in case of 'arg:' in cli_options string)
extern int optind; 		// the index of the next element to be processed in argv
						// The system initializes this value to 1
						// The caller can reset it to 1 to restart scanning of the same argv, 
						// or when scanning a new argument vector.
						// when the argv scan is done, optind is set to 0 (argv[0]=program name)

extern int opterr;		// if set to 0 prevents getopt() from printin error messages
extern int optopt;  	// if unknown option encountered, getopt() places it in optopt 

// defines


// types
 

// local objects 
static const char* const cli_options = "hvlm:"; // h:help, v:verbose, m:module+num
static const char* program_name;
int exit_code;

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
	int			rc;
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
	printf ("\n\nWelcome to %s, %d CLI options are being parsed ... \n\n", program_name, argc-1);

	// parse 
	exit_code = cli_parse (argc, argv, &cli_args);
	if (exit_code != EXIT_SUCCESS)
	{
		printf ("\n\n An error took place while parsing the CLI options, Quit\n\n");
		exit(-EXIT_FAILURE);
	}

	/* Done with options. OPTIND points to first nonoption argument.
	For demonstration purposes, print them if the verbose option was specified. */
	if (cli_args.verbose) 
	{
		for (int i=1; i<argc; ++i)
			printf ("Argument# %d: %s\n", i, argv[i]);
	}
	
	// if a module number provided - call it
	if ((cli_args.mdl_num > 0) && (cli_args.mdl_num <= get_num_of_us_modules()))
	{
		rc = call_module(cli_args.mdl_num);
		exit (rc);
	}

	// clean up 
	printf("\n\n CLI Module number (-m #) must be provided. Try calling with -h (Usage advise), Quit ...\n\n");
	exit (EXIT_SUCCESS);
}	
