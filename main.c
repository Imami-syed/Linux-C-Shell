#include "header.h"
#include "history.c"
#include "ls.c"
#include "usrnsplit.c"
#include "discover.c"
#include "pinfo.c"
#include "fg.c"
#include "fbp.c"
#include "cd.c"
char *usr;
char sys[maxlen];
int sysint;
char home[maxlen];
char dirpath2[maxlen];
char* fns[]={"cd", "ls", "exit", "history", "echo", "clear", "pwd", "pinfo", "discover", "sleep"};
char history[20][maxlen];
pid_t pid;
char *test1=";";
char test2[] = "' ','\t','\n'";
// char* discoverflags[]={"-d", "-f"};
char* and="&";
int main()
{
    int count=0, i=0;
    pid=getpid();
    usr=usrname(); //getting user name
    sysint=gethostname(sys, sizeof(sys)); //getting systemname
    printf("%s<%s%s@%s%s:~>%s", KCYN,KMAG,usr, sys,KCYN, KNRM);
    getcwd(home, sizeof(home)); //getting home directory path
    signal(SIGCHLD,signal_handler);
    while(1)
    {
        char a[maxlen];
        fgets(a, maxlen, stdin);
        //adding command to history
        add_hist(a, home); 
        if(!strcmp(a, "\n")) goto L2;
        strtok(a, "\n"); // removing the tailing \n that comes in input
        int count=0;
        char *commands[maxlen];
        commands[count] = strtok(a,test1);
        while (commands[count] != NULL)
        {
            count++;
            commands[count] = strtok(NULL, test1);
        }
        for(int i=0; i < count ; i++)
        {
            char *command2[maxlen];
            int j = 0;
            command2[j] = strtok(commands[i], test2);
            while (command2[j] != NULL)
            {
                j++;
                command2[j] = strtok(NULL, test2);
            }
            if(!strcmp(fns[0],command2[0])) //implementing cd command
            {
              cd_implement(command2, home);
            } 
            else if(!strcmp(fns[1],command2[0])) //implementing ls function
            {
                ls_implement2(command2, j, home);
            }
            else if(!strcmp(fns[2],command2[0])) //implementing exit function
                exit(0);
            else if(!strcmp(fns[3],command2[0])) //implementing history function
            {
                displayhistory(home);
            }
            else if(!strcmp(fns[4], command2[0])) //implementing echo command
            {
                for (int i = 1; i <= j-1; i++)
                {
                    printf("%s ", command2[i]);
                }
                printf("\n");
            }
            else if (!strcmp(fns[5], command2[0])) //implementing clear command
            {
                system("clear");
            }
            else if(!strcmp(fns[6], command2[0])) //implementing pwd command
            {   
                getcwd(dirpath2, sizeof(dirpath2));
                printf("%s\n", dirpath2);
            }
            else if(!strcmp(fns[7], command2[0])) //implementing pinfo command
            {   
                if (j == 2)
                {
                    pinfo(command2[1], home);
                }
                else if(j==1) 
                {
                    pinfo(NULL, home);
                }
                else{
                    perror("pinfo()");
                }
            }
            else if(!strcmp(fns[8], command2[0])) //implementing discover command
            {   
                discover_implement2(command2,home, j);
            }
            else{
                time_t begin = time(NULL);
                fg(command2, j);
                time_t end = time(NULL);
                if((end-begin) > 0)
                {    
                    char* strng="took ";
                    if(!strcmp(dirpath2,home))
                    {
                        printf("%s<%s%s@%s%s:~%s-%s%lds%s>%s", KCYN,KMAG,usr, sys,KCYN,KRED, strng, (end-begin), KCYN, KNRM);
                    }
                    else
                    {
                        printf("%s<%s%s@%s%s:%s%s-%s%lds%s>%s", KCYN,KMAG,usr, sys,KCYN,dirpath2,KRED, strng, (end-begin), KCYN, KNRM);
                    }
                    goto L3;
                }
            }
            L2:
        }
        getcwd(dirpath2, sizeof(dirpath2));
        if(!strcmp(dirpath2,home))
        {
            printf("%s<%s%s@%s%s:~>%s", KCYN,KMAG,usr, sys,KCYN, KNRM);
        }
        else
        {
            printf("%s<%s%s@%s%s:%s>%s", KCYN,KMAG,usr, sys,KCYN,dirpath2, KNRM);
        }
        L3:
    }
    L1:
    return 0;
}