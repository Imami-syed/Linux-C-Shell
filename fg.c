#include "header.h"
int tp=1;
void fg(char *cmds[maxlen], int j)
{
	char* and="&";
    int forknum=fork() ;
	int happen=0;
	if(!strcmp(cmds[j-1], and))
	{
		cmds[j-1]=NULL;
		happen=1;
	}
	else  cmds[j]==NULL;
	if(forknum == 0)
	{
		int x=execvp(cmds[0],cmds) ;
		if(x==-1)
		{
			printf("Cannot run background process\n") ;
			perror("execvp()") ;
		}
	}
	else if(forknum > 0)
	{
		if(happen == 0)
			wait(NULL);
		else{
			printf("[%d]\t%d\n",tp, forknum);
			tp++;
			return;
		}
	}
}