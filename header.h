#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <errno.h>
#include <signal.h>
// #include <assert.h>
// #include <limits.h>
// #include <math.h>
#define maxlen 4096
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

char* cd[]={"~", "-", ".", ".."};
char* ls[]={"-a", "-l", ".", "..", "~", "-al", "-la"};

struct proc{
    bool flag ;
    char name[maxlen] ;
    int pid;
} ;
struct proc process[maxlen] ;

//cd.c
void cd_implement(char* cmds[maxlen], char* home);

//ls.c
void ls_implement2(char* cmds[maxlen],int j, char* home);
void checkdirls(DIR* directory);
int isDir(const char* filename);
void printls(DIR* directory);
void printlsa(DIR* directory);
void printlsfile(char* filename, DIR* directory, char* cwd);
void printlsafile(char* filename, DIR* directory, char* cwd);
void printlslfile(char* filename, DIR* directory, char* cwd);
void printlslafile(char* filename, DIR* directory, char* cwd);
int caldirlsl(DIR* directory);
int caldirlsla(DIR* directory);
void lsl_call(DIR* directory);
void lsla_call(DIR* directory);
void printlsl(char* filepath, char* filename);

//discover.c
void discover_implement2(char* cmds[maxlen], char* home, int j);
void printdiscover2(DIR* directory, char* home);
void printdiscoverfiles(DIR* directory, char* home);
void discdir(DIR* directory, char* home);
void discdirname(char* filepath, DIR* directory, char* home);
void discdirname_f(char* filepath, DIR* directory, char* home);
void discdirname_d(char* filepath, DIR* directory, char* home);
void discfiles(DIR* directory, char* home);
void printnew(DIR* directory, char* home);
char* find_dir(char* filepath, char* home);

//history.c
void add_hist(char* a, char* home);
void load_hist(char* home);
void makechanges(char cmds[20][maxlen],char hm[100][maxlen], char*a);
void displayhistory(char* home);
void read_numline(char* home);

//pinfo.c
void pinfo(char* pid, char* home);
char* replace_home(char* rp, char* home);

//fg.c
void fg(char *cmds[maxlen], int j);

//fbp.c
void signal_handler();

//usrnsplit.c
char *usrname();
char** split(char* n , char* d, int *new);

#endif