#include "header.h"
void checkdirls(DIR* directory)
{
    if(directory==NULL)
    {
        printf("Error finding directory or file!");
    }
}
int isDir(const char* filename)
{
    struct stat path;
    stat(filename, &path);
    return S_ISREG(path.st_mode);
}
void printls(DIR* directory)
{
    struct dirent *direntdir;
    while ((direntdir = readdir(directory)) != NULL)
    {
        if (direntdir->d_name[0] != '.')
        {
            if(!isDir(direntdir->d_name))
                printf("%s%s%s\t", KRED,direntdir->d_name, KNRM);
            else 
                printf("%s\t", direntdir->d_name);
        }
    }
        printf("\n");
}
void printlsfile(char* filename, DIR* directory, char* cwd)
{
    struct dirent *direntdir;
    struct stat filedirec={0};
    char check1[maxlen], check2[maxlen];
    if(stat(filename, &filedirec) == 0)
    {
        if(S_ISDIR(filedirec.st_mode)) 
        {
            getcwd(check1, maxlen);
            chdir(filename);
            getcwd(check2, maxlen);
            if(!strcmp(check1, check2))
            {
                perror("ls");
                return;
            }
            DIR* directory;
            directory=opendir(".");
            checkdirls(directory);
            printls(directory);
            closedir(directory);
            chdir(cwd);
            return;
        }
    }
    while ((direntdir = readdir(directory)) != NULL)
    {
        if(isDir(filename) && !strcmp((direntdir->d_name), filename) )
            printf("%s\n", direntdir->d_name);
    }
    if(!isDir(filename))
        perror("ls");

}
void printlsafile(char* filename, DIR* directory, char* cwd)
{
    struct dirent *direntdir;
    struct stat filedirec={0};
    char check1[maxlen], check2[maxlen];
    if(stat(filename, &filedirec) == 0)
    {
        if(S_ISDIR(filedirec.st_mode)) 
        {
            getcwd(check1, maxlen);
            chdir(filename);
            getcwd(check2, maxlen);
            if(!strcmp(check1, check2))
            {
                perror("ls");
                return;
            }
            DIR* directory;
            directory=opendir(".");
            checkdirls(directory);
            printlsa(directory);
            closedir(directory);
            chdir(cwd);
            return;
        }
    }
    while ((direntdir = readdir(directory)) != NULL)
    {
        if(isDir(filename) && !strcmp((direntdir->d_name), filename) )
            printf("%s\n", direntdir->d_name);
    }
    if(!isDir(filename))
        perror("ls");

}
void printlslfile(char* filename, DIR* directory, char* cwd)
{
    struct dirent *direntdir;
    struct stat filedirec={0};
    char check1[maxlen], check2[maxlen];
    if(stat(filename, &filedirec) == 0)
    {
        if(S_ISDIR(filedirec.st_mode)) 
        {
            getcwd(check1, maxlen);
            chdir(filename);
            getcwd(check2, maxlen);
            if(!strcmp(check1, check2))
            {
                perror("ls");
                return;
            }
            DIR* directory;
            directory=opendir(".");
            checkdirls(directory);
            long long int total = caldirlsl(directory);
            printf("total %lld\n", total);
            rewinddir(directory);
            lsl_call(directory);
            closedir(directory);
            chdir(cwd);
            return;
        }
    }
    while ((direntdir = readdir(directory)) != NULL)
    {
        if(isDir(filename) && !strcmp((direntdir->d_name), filename) )
        {
            printlsl(filename, direntdir->d_name);   
        }
    }
    if(!isDir(filename))
        perror("ls");

}
void printlslafile(char* filename, DIR* directory, char* cwd)
{
    struct dirent *direntdir;
    struct stat filedirec={0};
    char check1[maxlen], check2[maxlen];
    if(stat(filename, &filedirec) == 0)
    {
        if(S_ISDIR(filedirec.st_mode)) 
        {
            getcwd(check1, maxlen);
            chdir(filename);
            getcwd(check2, maxlen);
            if(!strcmp(check1, check2))
            {
                perror("ls");
                return;
            }
            DIR* directory;
            directory=opendir(".");
            checkdirls(directory);
            long long int total = caldirlsla(directory);
            printf("total %lld\n", total);
            rewinddir(directory);
            lsla_call(directory);
            closedir(directory);
            chdir(cwd);
            return;
        }
    }
    while ((direntdir = readdir(directory)) != NULL)
    {
        if(isDir(filename) && !strcmp((direntdir->d_name), filename) )
            printlsl(filename, direntdir->d_name);   
    }
    if(!isDir(filename))
        perror("ls");
}
void printlsa(DIR* directory)
{
    struct dirent *direntdir;
    while ((direntdir = readdir(directory)) != NULL)
    {

        if (direntdir->d_name[0] == '.')
            printf("%s%s%s\t", KBLU,direntdir->d_name, KNRM);
        else if(!isDir(direntdir->d_name))
            printf("%s%s%s\t", KRED,direntdir->d_name, KNRM);
        else
            printf("%s\t", direntdir->d_name);
    }
    printf("\n");
}
int caldirlsl(DIR* directory)
{
    long long total =0;
    struct dirent *direntdir;
    struct stat filedirec={0};
    char filepath[maxlen];
    while((direntdir=readdir(directory))!=NULL)
    {
        getcwd(filepath,maxlen);
        strcat(filepath, "/");
        strcat(filepath, direntdir->d_name);
        if(direntdir->d_name[0] != '.')
        {
            if(stat(filepath, &filedirec)==0)
                total += filedirec.st_blocks;
        }
    }
    return total/2;
}
int caldirlsla(DIR* directory)
{
    long long total =0;
    struct dirent *direntdir;
    struct stat filedirec={0};
    // char path[maxlen];
    char filepath[maxlen];
    while((direntdir=readdir(directory))!=NULL)
    {
        getcwd(filepath,maxlen);
        strcat(filepath, "/");
        strcat(filepath, direntdir->d_name);
        if(stat(filepath, &filedirec)==0)
            total += filedirec.st_blocks;
    }
    return total/2;
}
void lsl_call(DIR* directory)
{
    struct dirent *direntdir;
    struct stat filedirec={0};
    char filepath[maxlen];
    while((direntdir=readdir(directory))!=NULL)
    {
        getcwd(filepath,maxlen);
        strcat(filepath, "/");
        strcat(filepath, direntdir->d_name);
        if(direntdir->d_name[0] != '.')
        {
           printlsl(filepath, direntdir->d_name);
        }
    }
}
void lsla_call(DIR* directory)
{
    struct dirent *direntdir;
    struct stat filedirec={0};
    char filepath[maxlen];
    while((direntdir=readdir(directory))!=NULL)
    {
        getcwd(filepath,maxlen);
        strcat(filepath, "/");
        strcat(filepath, direntdir->d_name);
        printlsl(filepath, direntdir->d_name);
    }
}
void printlsl(char* filepath, char* filename)
{
    struct stat filedirec={0};
    mode_t p=filedirec.st_mode;
    struct passwd *pws;
    struct group *grp;
    if(stat(filepath, &filedirec) != 0)
    {
        printf("No access to read file permission!");
    }
    else{
        if(S_ISDIR(filedirec.st_mode)) printf("d");
        else printf("-");
        if(filedirec.st_mode & S_IRUSR) printf("r");
        else printf("-");
        if(filedirec.st_mode & S_IWUSR) printf("w");
        else printf("-");
        if(filedirec.st_mode & S_IXUSR) printf("x");
        else printf("-");
        if(filedirec.st_mode & S_IRGRP) printf("r");
        else printf("-");
        if(filedirec.st_mode & S_IWGRP) printf("w");
        else printf("-");
        if(filedirec.st_mode & S_IXGRP) printf("x");
        else printf("-");
        if(filedirec.st_mode & S_IROTH) printf("r");
        else printf("-");
        if(filedirec.st_mode & S_IWOTH) printf("w");
        else printf("-");
        if(filedirec.st_mode & S_IXOTH) printf("x");
        else printf("-");
        printf(" %3ld  %s  %s  %6ld \t", filedirec.st_nlink, getpwuid(filedirec.st_uid)->pw_name, getgrgid(filedirec.st_gid)->gr_name, filedirec.st_size);
        char *time = ctime(&filedirec.st_mtime);
        for (int i = 4; i < 16; i++)
            printf("%c", time[i]);
        if(filename[0]=='.')
            printf("\t%s%s%s\n", KBLU, filename, KNRM);
        else if(!isDir(filename))
            printf("\t%s%s%s\n", KRED, filename, KNRM);
        else
           printf("\t%s\n", filename);

    }
}
void ls_implement2(char* cmds[maxlen],int j, char* home)
{
    DIR* directory;
    if(j == 1) // ls
    {
        directory = opendir(".");
        checkdirls(directory);
        printls(directory);
        closedir(directory);
    }
    else if (j==2) 
    {
        if(!strcmp(cmds[1], "."))
        {
            directory = opendir(".");
            checkdirls(directory);
            printls(directory);
            closedir(directory);
        }
        else if(!strcmp(cmds[1], ".."))
        {
            directory = opendir("./..");
            checkdirls(directory);
            printls(directory);
            closedir(directory);
        }
        else if(!strcmp(cmds[1], "-a"))
        {
            directory = opendir(".");
            checkdirls(directory);
            printlsa(directory);
            closedir(directory);
        }
        else if(!strcmp(cmds[1], "-l"))
        {
            directory=opendir(".");
            checkdirls(directory);
            long long int total = caldirlsl(directory);
            printf("total %lld\n", total);
            rewinddir(directory);
            lsl_call(directory);
            closedir(directory);
        }
        else if(!strcmp(cmds[1], "~"))
        {
            directory=opendir(home);
            checkdirls(directory);
            printlsa(directory);
            closedir(directory);
        }
        else if (!strcmp(cmds[1], "-la") || (!strcmp(cmds[1], "-al")))
        {
            directory=opendir(".");
            checkdirls(directory);
            long long int total = caldirlsla(directory);
            printf("total %lld\n", total);
            rewinddir(directory);
            lsla_call(directory);
            closedir(directory);
        }
        else
        {
            char cwd[maxlen];
            getcwd(cwd, maxlen);
            directory=opendir(".");
            checkdirls(directory);
            printlsfile(cmds[1], directory, cwd);
            closedir(directory);
        }

    }
    else{
        if(((j==3) && ((!strcmp(cmds[1], "-a")) && (!strcmp(cmds[2], "-l")))) || ((j==3) && ((!strcmp(cmds[1], "-l")) && (!strcmp(cmds[2], "-a"))))) //ls -a -l // ls -l -a
        {
            directory=opendir(".");
            checkdirls(directory);
            long long int total = caldirlsla(directory);
            printf("total %lld\n", total);
            rewinddir(directory);
            lsla_call(directory);
            closedir(directory);
        }
        int flaga=0, flagl=0;
        for(int k = 1; k<j; k++)
        {
            if(!strcmp(cmds[k], "-a"))
                flaga=1;
            if(!strcmp(cmds[k], "-l"))
                flagl=1;
            if(!strcmp(cmds[k], "-al"))
                flagl=1; flaga=1;
            if(!strcmp(cmds[k], "-la"))
                flagl=1; flaga=1;
        }
        for(int k = 1; k<j; k++)
        {
            if(!strcmp(cmds[k], "-a") || !strcmp(cmds[k], "-l") || !strcmp(cmds[k], "-la") || !strcmp(cmds[k], "-al"))
            {
                continue;
            }
            else 
            {
                printf("%s%s%s\n",KYEL,cmds[k],KNRM);
            }
            if(flaga==1 && flagl==1)
            {
                char cwd[maxlen];
                getcwd(cwd, maxlen);
                directory=opendir(".");
                checkdirls(directory);
                printlslafile(cmds[k], directory, cwd);
                closedir(directory); 
            }
            else if(flaga==1 && flagl==0)
            {
                char cwd[maxlen];
                getcwd(cwd, maxlen);
                directory=opendir(".");
                checkdirls(directory);
                printlsafile(cmds[k], directory, cwd);
                closedir(directory); 
            }
            else if(flaga==0 && flagl==1)
            {
                char cwd[maxlen];
                getcwd(cwd, maxlen);
                directory=opendir(".");
                checkdirls(directory);
                printlslfile(cmds[k], directory, cwd);
                closedir(directory); 
            }
            else 
            {
                char cwd[maxlen];
                getcwd(cwd, maxlen);
                directory=opendir(".");
                checkdirls(directory);
                printlsfile(cmds[k], directory, cwd);
                closedir(directory); 
            }
            printf("\n");
        }
    }
}