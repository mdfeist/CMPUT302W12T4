#include "XBoxThread.h"

#include <stdio.h>

int XBoxThread::startThread(){
	//build thread code

	//Test
	DWORD   dwThreadId;
	HANDLE  hThread = CreateThread( 
		NULL,                   // default security attributes
		0,                      // use default stack size  
		handleController,       // thread function name
		NULL,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadId);   // returns the thread identifier 

	if (hThread == NULL) 
        {
           printf("XBox Controller Thread could not be created.\n");
        }

	return 0;
}