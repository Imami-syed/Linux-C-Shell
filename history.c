#include "header.h"
int num_line=0;
char cmds[21][maxlen];
char hm[100][maxlen];
void read_numline(char* home)
{
    char histpath[maxlen];
    char cmds[21][maxlen];
    strcpy(histpath, home);
    strcat(histpath, "/history");
    FILE* file = fopen(histpath, "r"); 
    if(fopen==NULL) num_line = 0;
    char line[maxlen]; 
    int i = 0; 
    while (fgets(line, sizeof(line), file)) { 
        i++; 
    } 
    num_line = i;
    fclose(file); 
}
void load_hist(char* home)
{
    char histpath[maxlen];
    char cmds[21][maxlen];
    strcpy(histpath, home);
    strcat(histpath, "/history");
    FILE* file = fopen(histpath, "r");
    char line[maxlen]; int load_read=0;
    while(fgets(line, sizeof(line), file))
    {
        // printf("%s", line);
        strcpy(hm[load_read], line);
        load_read++;
    }
    fclose(file);
}
void add_hist(char* a, char* home)
{
    FILE* fp;
    char histpath[maxlen];
    strcpy(histpath, home);
    strcat(histpath, "/history");
    fp = fopen(histpath, "a+");
    read_numline(home);
    if(num_line==0)
    {
        fprintf(fp, "%s", a);   
        strcpy(cmds[num_line], a);
    }
    else if(num_line >= 0 && num_line < 20)
    {
        if(!strcmp(cmds[num_line-1], a)) goto L1;
        if(!strcmp(cmds[num_line], a)) goto L1;
        strcpy(cmds[num_line], a);
        fprintf(fp, "%s", a);   
    }
    else{
        if(!strcmp(cmds[num_line-1], a)) goto L1;   
        if(!strcmp(cmds[num_line], a)) goto L1;
        load_hist(home);
        makechanges(cmds, hm, a);
        strcpy(cmds[20], a);
        fclose(fp);
        fp=fopen(histpath, "w");
        for(int check=0; check<20; check++)
        {
            fprintf(fp, "%s", cmds[check]);   
        }
    }
    num_line++;
    L1:
    fclose(fp);
}
void makechanges(char cmds[20][maxlen], char hm[100][maxlen],char* a)
{
    int i;
    for(i=1; i<20; i++)
    {
        strcpy(cmds[i-1],hm[i]);
    }
    strcpy(cmds[i-1], a);
}
void displayhistory(char* home)
{
    char histpath[maxlen];
    char cmds[21][maxlen];
    strcpy(histpath, home);
    strcat(histpath, "/history");
    FILE* file = fopen(histpath, "r"); 
    char line[maxlen]; 
    int i = 0; 
    while (fgets(line, sizeof(line), file)) { 
        i++; 
        if(i>=num_line-10 && i <=num_line)
            printf("%s", line);
    } 
    // printf("%d\t", i);
    // printf("%d\n", num_line);
    fclose(file); 
}