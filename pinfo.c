#include "header.h"

char *replace_home(char *rp, char *home)
{
    char *result;
    int i, cnt = 0;
    char *newW = "~";
    int newWlen = strlen(newW);
    int homelen = strlen(home);
    for (i = 0; rp[i] != '\0'; i++)
    {
        if (strstr(&rp[i], home) == &rp[i])
        {
            cnt++;
            i += homelen - 1;
        }
    }
    result = (char *)malloc(i + cnt * (newWlen - homelen) + 1);
    i = 0;
    while (*rp)
    {
        if (strstr(rp, home) == rp)
        {
            strcpy(&result[i], newW);
            i += newWlen;
            rp += homelen;
        }
        else
            result[i++] = *rp++;
    }
    result[i] = '\0';
    return result;
}
void pinfo(char *pid, char *home)
{
    int intpid;
    char root[maxlen];
    if (pid == NULL)
    {
        intpid = getpid();
        strcpy(root, "/proc/self");
        chdir(root);
        char now[maxlen];
        getcwd(now, maxlen);
        char filepath[maxlen];
        strcpy(filepath, now);
        strcat(filepath, "/status");
        FILE *status = fopen(filepath, "r");
        if (status == NULL)
        {
            printf("file does not exist or doesn't work\n");
            return;
        }
        int linesearch = 3;
        int linesearch2=4;
        int linesearch3=7;
        char liner[maxlen];
        int line = 1;
        char req[maxlen]; char req2[maxlen]; char req3[maxlen];
        while (fgets(liner, 100, status)) // read the file string by string
        {
            if (linesearch == line)
            {
                for (int k = 0; k < strlen(liner); k++)
                {
                    req[k] = liner[k];
                }
            }
            if (linesearch2 == line)
            {
                for (int k = 0; k < strlen(liner); k++)
                {
                    req2[k] = liner[k];
                }
            }
            if (linesearch3 == line)
            {
                for (int k = 0; k < strlen(liner); k++)
                {
                    req3[k] = liner[k];
                }
            }
            line++;
        }
        printf("pid : %d\n", intpid);
        if(!strcmp(req2+6, req3+6)) 
        {
            printf("process status : %c+\n", req[7]);
        }
        else 
            printf("process status : %c\n", req[7]);
        fclose(status);
        strcpy(filepath, now);
        strcat(filepath, "/statm");
        char mem[maxlen];
        FILE *statm = fopen(filepath, "r");
        if (statm == NULL)
        {
            printf("Error!\n");
        }
        else
        {
            fscanf(statm, "%s%*[^\n]", mem); // not working very well...
        }
        fclose(statm);
        printf("Memory : %s\n", mem);
        char ep[maxlen];
        strcpy(filepath, now);
        strcat(filepath, "/exe");
        readlink(filepath, ep, sizeof(ep));
        char rp[maxlen];
        int cs = 0;
        while (cs < strlen(home))
        {
            break;
            cs++;
        }
        if (cs != strlen(home))
        {
            strcpy(rp, ep);
            rp[strlen(ep)] = '\0';
        }
        else
        {
            rp[0] = '~';
            rp[1] = '\0';
            strcat(rp, (const char *)&ep[strlen(home)]);
        }
        int j = 0;
        int i = 0;
        while (ep[i])
        {
            j++;
            ep[i++] = '\0';
        }
        char *execpath = replace_home(rp, home);
        printf("Executable Path : %s\n", execpath);
        chdir(home);
        return;
    }
    else
    {
        intpid = atoi(pid);
        strcpy(root, "/proc/");
        strcat(root, pid);
        chdir(root);
        char now[maxlen];
        getcwd(now, maxlen);
        if (strcmp(root, now))
        {
            perror("Process not found!");
            return;
        }
        char filepath[maxlen];
        strcpy(filepath, now);
        strcat(filepath, "/status");
        FILE *status = fopen(filepath, "r");
        if (status == NULL)
        {
            printf("file does not exist or doesn't work\n");
            return;
        }
         int linesearch = 3;
        int linesearch2=4;
        int linesearch3=7;
        char liner[maxlen];
        int line = 1;
        char req[maxlen]; char req2[maxlen]; char req3[maxlen];
        while (fgets(liner, 100, status)) // read the file string by string
        {
            if (linesearch == line)
            {
                for (int k = 0; k < strlen(liner); k++)
                {
                    req[k] = liner[k];
                }
            }
            if (linesearch2 == line)
            {
                for (int k = 0; k < strlen(liner); k++)
                {
                    req2[k] = liner[k];
                }
            }
            if (linesearch3 == line)
            {
                for (int k = 0; k < strlen(liner); k++)
                {
                    req3[k] = liner[k];
                }
            }
            line++;
        }
        printf("pid : %d\n", intpid);
        if(!strcmp(req2+6, req3+6)) 
        {
            printf("process status : %c+\n", req[7]);
        }
        else 
            printf("process status : %c\n", req[7]);
        fclose(status);
        strcpy(filepath, now);
        strcat(filepath, "/statm");
        char mem[maxlen];
        FILE *statm = fopen(filepath, "r");
        if (statm == NULL)
        {
            printf("Error!\n");
        }
        else
        {
            fscanf(statm, "%s%*[^\n]", mem); // not working very well...
        }
        fclose(statm);
        printf("Memory : %s\n", mem);
        char ep[maxlen];
        strcpy(filepath, now);
        strcat(filepath, "/exe");
        readlink(filepath, ep, sizeof(ep));
        char rp[maxlen];
        int cs = 0;
        while (cs < strlen(home))
        {
            break;
            cs++;
        }
        if (cs != strlen(home))
        {
            strcpy(rp, ep);
            rp[strlen(ep)] = '\0';
        }
        else
        {
            rp[0] = '~';
            rp[1] = '\0';
            strcat(rp, (const char *)&ep[strlen(home)]);
        }
        int j = 0;
        int i = 0;
        while (ep[i])
        {
            j++;
            ep[i++] = '\0';
        }
        char *execpath = replace_home(rp, home);
        printf("Executable Path : %s\n", execpath);
        chdir(home);
        return;
    }
}