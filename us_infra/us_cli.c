/*---------------------------------------------------------------------------------
 * us_cli.c
 * 
 * The module processes the command line and informs the main entry module
 * some results.
 *
 * It should be noticed that if the CLI asks for help (as for the command line options)
 * or in case an error takes place, then it takes the liberty to abort the process.
 *
 * Header file(s):
 * 	us_cli.h
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
extern int optind; 		// the index of the next element to be processed in argv
						// The system initializes this value to 1
						// The caller can reset it to 1 to restart scanning of the same argv, 
						// or when scanning a new argument vector.
						// when the argv scan is done, optind is set to 0 (argv[0]=program name)

extern int opterr;		// if set to 0 prevents getopt() from printin error messages
extern int optopt;  	// if unknown option encountered, getopt() places it in optopt 

// defines
#define	US_MDL_NONE		0	// US:User-Space, MDL:Module

// types


// local objects 
static const char* const cli_options = "hvlm:"; // h:help, v:verbose, m:module+num
static const char* program_name;
int exit_code;

// protoypes
static void disp_usage(bool should_abort, int exit_code);
static void show_us_modules (void);

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
				disp_usage (true, EXIT_SUCCESS); // print help to stdout and exit with success
				break;
				
			case 'v': // verbose
				cli_args->verbose = true;
				break;

			case 'm': // # of selected module
				cli_args->mdl_num = atoi(optarg);
				break;

			case 'l': // list available modules		
				show_us_modules();
				break;

			case '?': // invalid option encountered
				printf ("\n\nInvalid option encountered or missing argument for valid option \n\n");
				disp_usage (true, -EXIT_FAILURE); // print usage and exit
				break;
				
			case -1: // all CLI options successfully parsed
				// will never be executed as the main loop control breaks
				break;

			default: // Something else: unexpected.
				printf ("\nUnexpected event, Quit\n");
				disp_usage (true, -EXIT_FAILURE);
				break;
		}
	}
	
	// advise caller
	return (0);	
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

returns: 
	None
  ------------------------------------------------------------*/
static void show_us_modules (void)
{
	UINT num_of_modules;
	const char* mdl_topics;
	
	// get nm of modules
	num_of_modules = get_num_of_us_modules();
	
	// print table title
	printf ("\n Modules Table");
	
	// print modules list
	for (UINT i=1; i<=num_of_modules; i++)
	{
		mdl_topics = get_us_module_topics(i);
		printf ("\n [%d] - %s", i, mdl_topics);
	}
	
	// print table title
	printf ("\n\n");
	
	// unconditionally abort
	exit (0);
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
static void disp_usage (bool should_abort, int exit_code)
{
	fprintf (stdout, "\n");
	fprintf (stdout, "Usage: %s -m # [-l] [-h] [-v]\n", program_name);
	fprintf (stdout,
			" -h 	- Display usage \n"
			" -v 	- Enable Verbose \n"
			" -l  	- Show User-Space modules list\n"
			" -m # 	- Set User-Space module to be invoked\n"
			);
	fprintf (stdout, "\nComment: if -h or -l are requested the program displays the requested info and aborts\n\n");		
			
	// if program abort is required
	if (should_abort)
		exit (exit_code);
}

	
