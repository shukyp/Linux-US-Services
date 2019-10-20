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

#include "us_infra_inner.h"

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
static void show_usage(void);
static void show_cli_args(int argc, char** argv);


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
	cli_args - control structure to report CLI options tp caller

returns:
	int - exit code
		0 : CLI arguments string parsing successfully termintaed 
		* : any other value should be filtered by this function
  ------------------------------------------------------------*/
int cli_parse (int argc, char** argv, CLI_ARGS* cli_args)
{
	int 	opt;
	bool	h_option;
	bool	s_option;
	bool	l_option;
	
	// init
	opterr = 0;			// avoid getopt() printing errors by itself
	optind = 1;			// point to argv[1], just to be on safe side

	h_option = false;
	s_option = false;
	l_option = false;

	// set the program name
	program_name = argv[0];

	// traverse the CLI options string
	while ((opt = getopt(argc, argv, cli_options)) != -1)
	{				
		switch (opt)
		{
			case 'h': /* help */
				h_option = true;
				break;

			case 's': // list System features
				s_option = true;	
				break;

			case 'l': // list available modules
				l_option = true;		
				break;
							
			case 'v': // verbose
				cli_args->verbose = true;
				break;
				
			case 'm': // # of selected module
				cli_args->mdl_num = atoi(optarg);
				break;

			case '?': // error: invalid option encountered
				printf ("\n\nInvalid option encountered or missing argument for valid option \n\n");
				show_usage ();
				exit (EXIT_FAILURE);
				break;
				
			case -1: // success: all CLI options successfully parsed
				// will never be executed as the main loop control breaks
				break;

			default: // Something unexpected.
				printf ("\nUnexpected event, Quit\n");
				show_usage ();
				exit (EXIT_FAILURE);
				break;
		}
	}

	// if help requested
	if (h_option)
		show_usage (); // print help to stdout and exit with success

	// if list System features requested
	if (s_option)
		show_us_sys_features();

	// if list available modules requested
	if (l_option)
		show_us_modules();

	// if verbose requested 
	if (cli_args->verbose) 
		show_cli_args(argc, argv);

	// should we quit
	if (h_option || s_option || l_option)
		exit(EXIT_SUCCESS);
	
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
static void show_usage (void)
{
	fprintf (stdout, "\n");
	fprintf (stdout, "Usage: %s -m # [-l] [-h] [-v]\n", program_name);
	fprintf (stdout,
			" -h	- Display usage \n"
			" -s	- System features \n"
			" -v	- Enable Verbose \n"
			" -l	- Show User-Space modules list\n"
			" -m #	- Set User-Space module to be invoked\n"
			);
	fprintf (stdout, "\nComment: if -h or -l are requested the program displays the requested info and aborts\n\n");		
}


/*------------------------------------------------------------
function: 
	displays the actual CLI arguments  
	
description:	
	displays the actual CLI arguments one at a line

input:
	argc	- programs CLI options counter
	argv	- programs CLI options string

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
 
	
