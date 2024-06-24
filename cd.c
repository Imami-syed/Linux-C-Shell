#include "header.h"
char store[maxlen];
void cd_implement(char* cmds[maxlen], char* home){
    if(cmds[2] != NULL)
    {
        perror("cd");
        printf(" > too many arguments!\n");
        return;
    }
    if(cmds[1] == NULL)
    {
        getcwd(store, maxlen);
        chdir(home);
    }
    else if(!strcmp(cmds[1], cd[0]))
    {
        getcwd(store, maxlen);
        chdir(home);
    }
    else if(!strcmp(cmds[1], cd[1]))
    {
        chdir(store);
    }
    else if(!strcmp(cmds[1], cd[2]))
    {
        getcwd(store, maxlen);
        char cd3change[maxlen];
        getcwd(cd3change, maxlen);
        chdir(cd3change);
    }
    else if(!strcmp(cmds[1], cd[3]))
    {
        getcwd(store, maxlen);
        chdir(cmds[1]);
    }
    else
    {
        char check[maxlen];
        getcwd(store, maxlen);
        chdir(cmds[1]);
        getcwd(check, maxlen);
        if(!strcmp(check, store))
        {
            printf("cd : No such file or directory ! : %s\n", cmds[1]);
            return;
        }
    }
}