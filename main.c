#include <stdio.h>

#include "file1.h"
#include "file2.h"

/*---------------------------------------
 * 
 * Main entry to application
 * 
 * --------------------------------------*/
int main(int argc, char** argv)
{
	printf ("program [%s] got %d CLI arguments", argv[0], argc-1);
	
	printf("\n\nHello from Linux-User-Space code\n\n");
	func1();
	func2();
	return 0;
}
