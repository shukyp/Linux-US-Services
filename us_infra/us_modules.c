/*---------------------------------------------------------------------------------
 * us_modules.c
 * 
 * The module holds the information about the various modules of the project.
 * By using the term module, I refer to a specific issues that is being covered.
 * The term 'us' stands for 'user space'
 *  
 * Header file(s):
 * 	(1) us_modules.h
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
#include "us_modules.h"


// extern objects


// defines


// types
typedef struct us_mdl_info
{
	char* descr;
	int (*entry_func)(void);
} US_MDL_INFO; 


// local objects 
static US_MDL_INFO const us_mdls[] = 
	{
		{"Processes Creation, Managment, Destroy", 	(int (*)(void))NULL}, 
		{"Inter Process Communication", 			(int (*)(void))NULL}, 
		{"Inter Thread Communication", 				(int (*)(void))NULL}
	};

static UINT num_of_modules = (sizeof(us_mdls)/sizeof(US_MDL_INFO));	
 		

// protoypes



/*------------------------------------------------------------
function: 
	returns the number of supported modules 
	
input:	
	None
	
returns: 
	int - number of supported modules 
  ------------------------------------------------------------*/
 UINT get_num_of_us_modules(void)
 {
	 return (num_of_modules);
 }
 
 
/*------------------------------------------------------------
function: 
	returns specifc us_module description if input module number
	is valid. otherwise, NULL is returned.
	
input:	
	us_mdl_num - module number
	
returns: 
	char* - requested module info
  ------------------------------------------------------------*/
const char* const get_us_module_topics(UINT us_mdl_num)
{
	// valid module number
	if (us_mdl_num <= num_of_modules)
		return (us_mdls[us_mdl_num-1].descr);

	// invalid module number
	return (NULL); 
 }
 
  
/*------------------------------------------------------------
function: 
	returns specifc us_module description if input module number
	is valid. otherwise, NULL is returned.
	
input:	
	us_mdl_num - module number
	
returns: 
	int - return code
  ------------------------------------------------------------*/
int call_module (UINT us_mdl_num)
{
	int rc;
	
	// if valid module number
	if (us_mdl_num <= num_of_modules)
	{
	    rc = (*us_mdls[us_mdl_num-1].entry_func)();
	    return (rc);
	}

	// invalid us_module number
	return (-EXIT_FAILURE);		
}
