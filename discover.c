#include "header.h"
void printdiscover2(DIR* directory, char* home)
{
    char cwd[maxlen];
    char* dirname="";
    struct dirent *direntdir;
    char filepath[maxlen];
    char* req;
    getcwd(cwd, maxlen);
    while ((direntdir = readdir(directory)) != NULL)
    {
        if (direntdir->d_name[0] != '.')
        {
            getcwd(filepath, maxlen);
            strcat(filepath, "/");
            strcat(filepath, direntdir->d_name);
            req=find_dir(filepath, home);
            printf("%s\n", req);
            struct stat filedirec={0};
            if(stat(filepath, &filedirec) == 0)
            {
                if(S_ISDIR(filedirec.st_mode)) 
                {
                    chdir(filepath);
                    req=find_dir(filepath, home);
                    DIR* directory;
                    directory=opendir(".");
                    checkdirls(directory);
                    printdiscoverfiles(directory, home);
                    closedir(directory);
                    chdir(cwd);
                }
            }
        }

    }
}
void discdir(DIR* directory, char* home)
{
    char cwd[maxlen];
    char* dirname="";
    struct dirent *direntdir;
    char filepath[maxlen];
    char* req;
    getcwd(cwd, maxlen);
    while ((direntdir = readdir(directory)) != NULL)
    {
        if (direntdir->d_name[0] != '.')
        {
            getcwd(filepath, maxlen);
            strcat(filepath, "/");
            strcat(filepath, direntdir->d_name);
            req=find_dir(filepath, home);
            struct stat filedirec={0};
            if(stat(filepath, &filedirec) == 0)
            {
                if(S_ISDIR(filedirec.st_mode)) 
                {
                    printf("%s\n", req);
                    chdir(filepath);
                    req=find_dir(filepath, home);
                    DIR* directory;
                    directory=opendir(".");
                    checkdirls(directory);
                    discdir(directory, home);
                    closedir(directory);
                    chdir(cwd);
                }
            }
        }

    }
}
void discdirname(char* filepath, DIR* directory, char* home)
{
    char cwd[maxlen];
    char* dirname="";
    struct dirent *direntdir;
    struct stat filedirec={0};
    char* req;
    getcwd(cwd, maxlen);
    if(stat(filepath, &filedirec) == 0)
    {
        req=find_dir(filepath, home);
        chdir(filepath);
        DIR* directory;
        directory=opendir(".");

        checkdirls(directory);
        printdiscover2(directory, home);
        // printdiscoverfiles(directory, home);
        closedir(directory);
        chdir(cwd);
        return;
    }
    if(!isDir(filepath))
        perror("discover");
}
void discdirname_f(char* filepath, DIR* directory, char* home)
{
    char cwd[maxlen];
    char* dirname="";
    struct dirent *direntdir;
    struct stat filedirec={0};
    char* req;
    getcwd(cwd, maxlen);
    if(stat(filepath, &filedirec) == 0)
    {
        req=find_dir(filepath, home);
        chdir(filepath);
        DIR* directory;
        directory=opendir(".");
        checkdirls(directory);
        printdiscoverfiles(directory, home);
        closedir(directory);
        chdir(cwd);
        return;
    }
    if(!isDir(filepath))
        perror("discover");
}
void discdirname_d(char* filepath, DIR* directory, char* home)
{
    char cwd[maxlen];
    char* dirname="";
    struct dirent *direntdir;
    struct stat filedirec={0};
    char* req;
    getcwd(cwd, maxlen);
    if(stat(filepath, &filedirec) == 0)
    {
        req=find_dir(filepath, home);
        chdir(filepath);
        DIR* directory;
        directory=opendir(".");
        checkdirls(directory);
        discdir(directory, home);
        closedir(directory);
        chdir(cwd);
        return;
    }
    if(!isDir(filepath))
        perror("discover");
}
void printdiscoverfiles(DIR* directory, char* home)
{
    char cwd[maxlen];
    char* dirname="";
    struct dirent *direntdir;
    char filepath[maxlen];
    char* req;
    getcwd(cwd, maxlen);
    while ((direntdir = readdir(directory)) != NULL)
    {
        if (direntdir->d_name[0] != '.')
        {
            getcwd(filepath, maxlen);
            strcat(filepath, "/");
            strcat(filepath, direntdir->d_name);
            req=find_dir(filepath, home);
            struct stat filedirec={0};
            if(stat(filepath, &filedirec) == 0)
                if(!S_ISDIR(filedirec.st_mode)) 
                    printf("%s\n", req);
        }

    }
}
char* find_dir(char* filepath, char* home)
{
    char* result;
    int i, cnt = 0;
    char *newW=".";
    int newWlen = strlen(newW);
    int homelen = strlen(home);
    for (i = 0; filepath[i] != '\0'; i++) {
        if (strstr(&filepath[i], home) == &filepath[i]) {
            cnt++;
            i += homelen - 1;
        }
    }
    result = (char*)malloc(i + cnt * (newWlen - homelen) + 1);
    i = 0;
    while (*filepath) {
        if (strstr(filepath, home) == filepath) {
            strcpy(&result[i], newW);
            i += newWlen;
            filepath += homelen;
        }
        else
            result[i++] = *filepath++;
    }
    result[i] = '\0';
    return result;
}
void discover_implement2(char* cmds[maxlen], char* home, int j)
{
    //discover . "osn.txt"
    //discover ./OSN "a.txt"
    char invoke[maxlen];
    DIR *directory;
    getcwd(invoke, maxlen);
    if(j==1)
    {
        //discover
        directory = opendir(".");
        checkdirls(directory);
        printf(".\n");
        printdiscover2(directory, invoke);
        closedir(directory);
    }
    else if(j ==2)
    {
        if(!strcmp(cmds[1], "."))
        {
            //discover .
            directory = opendir(".");
            checkdirls(directory);
            printf(".\n");
            printdiscover2(directory, invoke);
            closedir(directory);
        }
        else if(!strcmp(cmds[1], ".."))
        {
            //discover ..
            char invoke2[maxlen];
            directory = opendir("./..");
            chdir("..");
            getcwd(invoke2, maxlen);
            checkdirls(directory);
            printf(".\n");
            printdiscover2(directory, invoke2);
            closedir(directory);
            chdir(invoke);
        }
        else if(!strcmp(cmds[1], "~"))
        {
            //discover ~
            directory = opendir(home);
            checkdirls(directory);
            printf(".\n");
            printdiscover2(directory, invoke);
            closedir(directory);
        }
        else if(!strcmp(cmds[1], "-d"))
        {
            //discover -d # the command searches for all
                // the directories in the current directory hierarchy
            directory = opendir(".");
            checkdirls(directory);
            printf(".\n");
            discdir(directory, invoke);
            closedir(directory);
        }
        else if(!strcmp(cmds[1], "-f"))
        {
            //discover -f → searches for all files
            directory = opendir(".");
            checkdirls(directory);
            printf(".\n");
            printdiscoverfiles(directory, invoke);
            closedir(directory);
            
        }
        else{
            //discover dirname
            //discover dirpath
            directory = opendir(".");
            checkdirls(directory);
            printf(".\n");
            discdirname(cmds[1],directory, invoke);
            closedir(directory);

        }
    }
    else{
        if(((j==3) && (!strcmp(cmds[1], "-d") && !strcmp(cmds[2], "-f"))) || ((j==3) && (!strcmp(cmds[1], "-f") && !strcmp(cmds[2], "-d"))))
        {
            //discover -d -f || discover -f -d
            directory = opendir(".");
            checkdirls(directory);
            printf(".\n");
            printdiscover2(directory, invoke);
            closedir(directory);
        }
        else if(((j==3) && (!strcmp(cmds[1], "-f") || !strcmp(cmds[2], "-f"))))
        {
            directory = opendir(".");
            checkdirls(directory);
            printf(".\n");
            discdirname_f(cmds[1],directory, invoke);
            closedir(directory);
        }
        else if(((j==3) && (!strcmp(cmds[1], "-d") || !strcmp(cmds[2], "-d"))))
        {
            directory = opendir(".");
            checkdirls(directory);
            printf(".\n");
            discdirname_d(cmds[1],directory, invoke);
            closedir(directory);
        }
       
    }
}