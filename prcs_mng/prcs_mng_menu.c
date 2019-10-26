/*---------------------------------------------------------------------------------
 * prcs_mng_menu.c
 * 
 * The module presents the prcs_mng local menu.
 * It presents the menu and interacts with the user.
 * At user request, it either calls the requested facility or exits
 *  
 * Header file(s):
 * 	- prcs_us.h
 * 	- prcs_mng_inner.h
 *
 * 
 * 
 * Evolution table:
 * 
 * Version	Date				Action
 * ---------------------------------------------------------------------------------
 * 		1	Oct. 25, 2019	Created
 * 
 * 
 * 
 *
 * 
 *** Author: Shuky Persky
 *
 *
 * Comments on Beep:
 * ------------------
 * 	if terminal doesn't beep, one can:
 * 	1. sudo modprobe pcspkr
 * 	2. sudo apt-get install beep
 * -----------------------------------------------------------------------------------*/

// includes
#include <stdio.h>
#include <termios.h>

#include "prcs_mng_inner.h"

// extern objects


// defines


// types


// local objects 

// protoypes
static void show_menu(void);
static void enter_to_cont(void);	


/*------------------------------------------------------------
function: 
	prcs_mng main entry point.
	it presnts the module menu and executes users requests 
	
input:	
	verbose - indicates whether verbose mode on enabled

returns: 
	none
  ------------------------------------------------------------*/
int prcs_mng_menu (bool verbose)
{
	int user_selection;

	// show menu
	show_menu();

	// get/process user input
	while(1)
	{
		// get user request
		scanf("%d", &user_selection);

		// analysze user request, execute it (if valid)
		switch (user_selection)
		{
			case 0:
				printf ("\n\n\n");
				return(EXIT_SUCCESS);
				//break;
				
			case 1: //Show Current Process Info
				display_process_info();
				enter_to_cont();
				show_menu();
				break;
				 
			case 2: // Show Current process Resource Utilization & Limits
				display_process_resource_usage_and_limits();
				enter_to_cont();
				show_menu();		
				break;
				 
			case 3: // Create child process (using fork) and Watch its termination 
				prcs_create_single_child_using_fork();
				enter_to_cont();
				show_menu();		
				break;
				 
			case 4: // Create child process (using vfork) and Watch its termination
				printf("\n NOT IMPLEMENTED YET ...");
				enter_to_cont();			
				show_menu();		
				break;
				 
			case 5: // Create a single child process (using vfork) and Watch its kill termination)
				printf("\n NOT IMPLEMENTED YET ...");
				enter_to_cont();			
				show_menu();				
				break;
				 
			case 6: // Create a few children processes (using vfork) and Watch their termination
				printf("\n NOT IMPLEMENTED YET ...");
				enter_to_cont();			
				show_menu();		
				break;

			case 7: // Parent and child have separate address space
				printf("\n NOT IMPLEMENTED YET ...");
				enter_to_cont();			
				show_menu();		
				break;

			case 8: // Process Scheduling/Prioritization
				printf("\n NOT IMPLEMENTED YET ...");
				enter_to_cont();			
				show_menu();		
				break;								
				 
			default:
				 printf("\a"); // bell sound
				 getchar();
				 break;
		}
	}
 }


/*------------------------------------------------------------
function: 
	presents the menu options.
	
input:	
	None

returns: 
	None
  ------------------------------------------------------------*/
static void show_menu(void)
{
 	printf("\n\n\n");
	printf("\n\t\t\t\t\t    	========= Process Manage ========= \n");
	printf("\n\t\t\t\t\t   (see comments in file if terminal doesn't beep)\n");
	printf("\n\n\t\t		1. Show Current Process Info ");
	printf("\n\n\t\t		2. Show Current process Resource Utilization & Limits ");
	printf("\n\n\t\t		3. Create child process (using fork) and Watch its termination ");
	printf("\n\n\t\t		4. Create child process (using vfork) and Watch its termination (-)");	
	printf("\n\n\t\t		5. Create a single child process (using vfork) and Watch its kill termination (-) ");
	printf("\n\n\t\t		6. Create few children processes (using vfork) and Watch their termination (-)");
	printf("\n\n\t\t		7. Parent and child have separate address space (-)");	
	printf("\n\n\t\t		8. Process Scheduling/Prioritization (-)");
	printf("\n\n\t\t		0. Exit");

	printf("\n\n\t\t		Please Select : ");
}


/*------------------------------------------------------------
function: 
	blocks execution until ENTER is hit
	
input:	
	None

returns: 
	None
  ------------------------------------------------------------*/
static void enter_to_cont(void)
{
	char c;
	
	//let user know
	printf("\n >>> Hit ENTER key to continue ...");

	// clean buffer
	c = getchar();
			
	// await user's 'go ahead'
	while (1)
	{
		c = getchar();
		//printf ("\n c=[%c]", c);
		if (c == '\n')
			break;
		//sleep(3);
	}
}

