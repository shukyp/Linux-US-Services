/*---------------------------------------------------------------------------------
 * prcs_create_single_child_using_fork.c
 * 
 * The module creates a single child process using fork
 *
 * Header file(s):
 * 	prcs_mng_inner.h
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
 * -----------------------------------------------------------------------------------*/

// includes
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/resource.h>
#include <sys/wait.h>

#include <stdio.h>

#include "prcs_mng_inner.h"

// extern objects

// defines

// types

// local objects 

// protoypes
static void child_work (void);
static void parent_work (void);
static bool watch_child_termination(void);

 
/*------------------------------------------------------------
function: 
	create a child process using fork  
	
input:	
	none

returns: 
	none
  ------------------------------------------------------------*/
void prcs_create_single_child_using_fork (void)
{
	bool child_process_alive;

	// init
	child_process_alive = false;
	
	// prent process creates a chile process
	pid_t	child_pid;

	// create the child process
	child_pid = fork();
	child_process_alive = true;

	// fork failed
	// errno can be either of the following:
	// a. EAGAIN: kernel failed allocating resources for the child process
	// b. RLIMIT_NPROC: child process exceeded allowed resorces
	// c. ENOMEM: Kernel could not allocate enough memory to complete the fork
	//
	// if a failure took place the child process doesn't exist and the parent
	// continues with its pending tasks
	if (child_pid < 0)
	{
		perror(" ... fork() faild");
		return;
	}

	// ---- Being here, it means that fork() succedded ----

	// child process goes here
	if (child_pid == 0)
	{
		child_work();

		printf("\n\n CHILD report: terminating successfully");
		exit(EXIT_SUCCESS);
	}

	// parent goes here as it gets the PID of the created child process
	// (which is not negative (as of failure), or zero (as for the child process)
	//
	// The parent is doing some work while watching its children termination
	printf ("\n\n\a Parent of PID: %ld Just created  its child process of PID: %ld",
					(ULINT)getpid(), (ULINT)child_pid);
	do
	{
		// do some work		
		parent_work();

		// watch
		if (child_process_alive)
			child_process_alive = watch_child_termination();

		// sleep a bit
		sleep(1);

		// exit current work
		if (!child_process_alive)
		{
			printf("\n\n PARENT report: Exiting ...");
			break;
		}
		
	} while (1);
}


/*------------------------------------------------------------
function: 
	child pseudo work  
	
input:	
	none

returns: 
	none
  ------------------------------------------------------------*/
static void child_work (void)
{
	#define	CHILDS_LOOPS	10
	
	ULINT	pid = (ULINT)getpid();
	
	printf("\n\n In child of PID: %ld", pid);
	
	for (int i=0; i<CHILDS_LOOPS; i++)
	{
		printf("\n [%d/%d] CHILD pid %ld is worling very hard", i+1, CHILDS_LOOPS, pid);
		sleep(2);
	}
}


/*------------------------------------------------------------
function: 
	parent pseudo work  
	
input:	
	none

returns: 
	none
  ------------------------------------------------------------*/
static void parent_work (void)
{
	printf("\nParent is working extremly hard...");
}


/*------------------------------------------------------------
function: 
	checks if child process terminated/stopped. In case one is
	found, the reasons are enquired and reported.  
	
input:	
	none

returns: 
	none
  ------------------------------------------------------------*/
static bool watch_child_termination(void)
{
	pid_t				pid;
	int				status;
	int 				options;
	struct rusage	rusage;
	
	// init
	status = 0;
	options = WNOHANG | WUNTRACED; // WNOHANG-non-blocking, WUNTRACED-stopped process
	memset(&rusage, 0, sizeof(rusage));
	
	// checking child process status
	// if no child terminated the call return with pid==0
	pid = wait3(&status, options, &rusage);

	// if no child terminated yet
	if (pid == 0)
		return (true);;

	// ---- a child termintaed. Lets see what we have here -----
	// in the below enquiry we refrain from going into the resource usage report

	// if the process termintaed successfully thru its main() function
	if (WIFEXITED(status))
	{
		printf ("\n\n Parent report: CHILD process PID: %ld terminated succesfully with exit code %d", (ULINT)pid, WEXITSTATUS(status));
		return (false);
	}

	// if the child process terminated due to signal
	if (WIFSIGNALED(status))
	{
		printf ("\n\n Parent report: CHILD process PID: %ld terminated by signal %d", (ULINT)pid, WTERMSIG(status));
		return (false);
	}
	
	// if the child process stopped due to signal
	if (WIFSTOPPED(status))
	{
		printf ("\n\n Parent report: CHILD process PID: %ld terminated as stopped by signal %d", (ULINT)pid, WSTOPSIG(status));
		return (false);
	}

	// logic should never reach this poing
	// being here it means there is no child process
	return (false);
}
		

