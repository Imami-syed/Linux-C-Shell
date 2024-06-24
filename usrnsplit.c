#include "header.h"

char *usrname()
{
    struct passwd *pws;
    pws = getpwuid(geteuid());
    return pws->pw_name;
}
char** split(char* n , char* d, int *new) {
    char ** sub_str = malloc(maxlen * sizeof(char*));
    char *portion=strtok(n,d);
    int  i =0;
    while(portion!=NULL)
    {
        sub_str[i] = malloc(maxlen * sizeof(char));
        sub_str[i]=portion;
        portion=strtok(NULL,d);
        i++;
    }
    *new=i;
    return sub_str;
}
