#include "header.h"
void signal_handler()
{
    int status ;
	int pid=waitpid(-1,&status,WNOHANG) ;
	if(pid>0)
	{
		if(WIFEXITED(status))
		{
			printf("\npid %d exited normally\n", pid);
		}
		else{
			printf("\npid %d exited abnormally\n", pid);
		}
	}
	// exit(status);
}