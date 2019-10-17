/*---------------------------------------------------------------------------------
 * us_cli.c
 * 
 * The module processes the command line options and invoke the appropriate
 * facility to execute the indicated CLI option(s).
 *
 * It should be noticed that if the CLI options include the help option,
 * list available modules, or the system features list option,
 * or if an error takes place, then this facility (CLI parser) takes the
 * liberty to abort the whole process after serving the requests.
 *
 * The logic of this module is designed to termonate the whole process in
 * case any issue is encountered.
 *
 * Header file(s):
 * 	- us_cli.h
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

#include "us_cli.h"
#include "us_modules.h"

// extern objects
extern char *optarg;	// argument value of the option	(in case of 'arg:' in cli_options string)
extern int optind; 	// the index of the next element to be processed in argv
							// The system initializes this value to 1
							// The caller can reset it to 1 to restart scanning of the same argv, 
							// or when scanning a new argument vector.
							// when the argv scan is done, optind is set to 0 (argv[0]=program name)

extern int opterr;	// if set to 0 prevents getopt() from printin error messages
extern int optopt;  	// if unknown option encountered, getopt() places it in optopt 

// defines

// types

// local objects 
static const char* const cli_options = "hslvm:"; 	// h:help,
																	// s:system-features
																	// l:list available modules
																	// v:verbose
																	// m:module+num
static const char* program_name;

// protoypes
static void show_usage(bool should_abort, int exit_code);


/*------------------------------------------------------------
function: 
	parses the CLI arguments string 
	
description:	
	if -h (help) is encountered, the function handles the request and aborts
	if -l (modules list) is encountered, the function handles the request and aborts
	in any other case (see return values below) the function reports its caller 
	to handle the reeported returned value

input:
	argc	- programs CLI options counter
	argv	- programs CLI options string
	cli_args - control structure to report CLI options

returns:
	int - exit code
		0 : CLI arguments string parsing successfully termintaed 
		* : any other value should be filtered by this function
  ------------------------------------------------------------*/
int cli_parse (int argc, char** argv, CLI_ARGS* cli_args)
{
	int opt;
	
	// init
	opterr = 0;			// avoid getopt() printing errors by itself
	optind = 1;			// point to argv[1], just to be on safe side

	// traverse the CLI options string
	while ((opt = getopt(argc, argv, cli_options)) != -1)
	{				
		switch (opt)
		{
			case 'h': /* help */
				show_usage (true, EXIT_SUCCESS); // print help to stdout and exit with success
				break;

			case 's': // list System features
				show_us_sys_features();
				break;

			case 'l': // list available modules		
				show_us_modules();
				break;
							
			case 'v': // verbose
				cli_args->verbose = true;
				break;
				
			case 'm': // # of selected module
				cli_args->mdl_num = atoi(optarg);
				break;

			case '?': // error: invalid option encountered
				printf ("\n\nInvalid option encountered or missing argument for valid option \n\n");
				show_usage (true, -EXIT_FAILURE); // print usage and exit
				break;
				
			case -1: // success: all CLI options successfully parsed
				// will never be executed as the main loop control breaks
				break;

			default: // Something unexpected.
				printf ("\nUnexpected event, Quit\n");
				show_usage (true, -EXIT_FAILURE);
				break;
		}
	}

	// being here means that CLI options successfully processed w/o any error	
	// if verbose requested, print all given optons 
	if (cli_args->verbose) 
	{
		for (int i=1; i<argc; ++i)
			printf ("Argument# %d: %s\n", i, argv[i]);
	}
	
	// advise caller
	return (EXIT_SUCCESS);	
}


/*------------------------------------------------------------
function: 
	displays the right call to this program 
	
description:	
	prints a message which indicates how to call this program with 
	reference to the various CLI options 
	
	if the reason for calling this function is due to the
	user's request for help then the functions aborts the program.

input:
	should_abort - should the function abort the program
	exit_code - if function aborts then what is the exit code

returns: 
	None
  ------------------------------------------------------------*/
static void show_usage (bool should_abort, int exit_code)
{
	fprintf (stdout, "\n");
	fprintf (stdout, "Usage: %s -m # [-l] [-h] [-v]\n", program_name);
	fprintf (stdout,
			" -h 	   - Display usage \n"
			" -s     - System features \n"
			" -v 	   - Enable Verbose \n"
			" -l  	- Show User-Space modules list\n"
			" -m # 	- Set User-Space module to be invoked\n"
			);
	fprintf (stdout, "\nComment: if -h or -l are requested the program displays the requested info and aborts\n\n");		
			
	// if program abort is required
	if (should_abort)
		exit (exit_code);
}
 
	
