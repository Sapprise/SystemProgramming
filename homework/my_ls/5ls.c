/*************************************************************************
	> File Name: 5ls.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年05月06日 星期一 17时05分01秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <dirent.h>
#include <pwd.h>
#include <utime.h>
#include <time.h>
#include <grp.h>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

#ifndef FILE_MAX
#define FILE_MAX 1024
#endif

char fileName[FILE_MAX][FILENAME_MAX];

int rwxMode[] = {0, S_IRUSR, S_IWUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};

char getFileType(mode_t mode) {
    if (S_ISDIR(mode)) return 'd';
    else if (S_ISCHR(mode)) return 'c';
    else if (S_ISBLK(mode)) return 'b';
    else if (S_ISFIFO(mode)) return 'f';
    else if (S_ISLNK(mode)) return 'l';
    else if (S_ISSOCK(mode)) return 's';
    else return '-';
}

bool cmp(string s1, string s2) {
    return s1<s2;
}

void sort(char array[][FILENAME_MAX], int n){
    int i,j;
    char temp[FILENAME_MAX];
    for(i = n-1; i >= 0; --i)
        for(j = 0; j < i; ++j)
    if(strcmp(array[j], array[j+1]) > 0){
                strcpy(temp, array[j]);
                strcpy(array[j], array[j+1]);
                strcpy(array[j+1], temp);
              
    }
}

void printf_ls_al(int argc, char *if_al) {
    char *dirPath;
    DIR * dirp;
    if(argc >= 3) {
        dirPath = if_al; 
        dirp = opendir(dirPath);
    } else { 
            dirp = opendir(".");
            if(getcwd(dirPath, FILENAME_MAX) == NULL){
            perror("getcwd returns error");
            exit(EXIT_FAILURE);
    }
        }

        if(dirp == NULL){
            perror("opendir returns error");
            exit(EXIT_FAILURE);
        }
        int filen = 0, i, j;
        while(1){
            struct dirent * fileInfo = readdir(dirp);
            if(fileInfo == NULL) break;
            strcpy(fileName[filen++], fileInfo->d_name);
        }
        sort(fileName, filen);
        for(i = 0; i < filen; ++i){
            struct passwd * userInfo;
            struct group * groupInfo;
            struct stat fileStat;
            struct tm *mTime;
            char fileMode[11], filePath[FILENAME_MAX];
                if(dirPath[strlen(dirPath)-1] != '/')
                    sprintf(filePath,"%s/%s",dirPath, fileName[i]);
                else sprintf(filePath, "%s%s",dirPath, fileName[i]);
                if(stat(filePath, &fileStat) < 0){
                    perror("stat returns error");
                    exit(EXIT_FAILURE);
                    
            }
                strcpy(fileMode, "-rwxrwxrwx");
                fileMode[0] = getFileType(fileStat.st_mode);
                for(j = 1; j < 10; ++j)
                    if(!(fileStat.st_mode & rwxMode[j])) fileMode[j] = '-';

                userInfo = getpwuid(fileStat.st_uid);
                groupInfo = getgrgid(fileStat.st_gid);
            if(userInfo == NULL || groupInfo == NULL){
                    perror("getpwuid returns error");
                    exit(EXIT_FAILURE);
                    
            }
            mTime = localtime(&fileStat.st_mtime);
            printf("%s %2d %8s %8s %5d %2d月 %2d %02d:%02d %s\n",fileMode,fileStat.st_nlink,userInfo->pw_name, groupInfo->gr_name,(int)fileStat.st_size,mTime->tm_mon+1, mTime->tm_mday, mTime->tm_hour, mTime->tm_min, fileName[i]); 
              
        }
}

void printf_ls(int argc, char * if_ls) {
    char *dirPath;
    char s[100];
    DIR *dir;
    string res[1000];
    struct dirent *rent;//struct
    if(argc >= 2) {
        dirPath = if_ls;
        dir = opendir(dirPath);
    }
        else{
            dir = opendir(".");
            if(getcwd(dirPath, FILENAME_MAX) == NULL){
            perror("getcwd returns error");
            exit(EXIT_FAILURE);
    }
  }
    int cnt = 0;
    int maxlength = 0;
    struct winsize size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    while((rent=readdir(dir)))//利用dirent中的readdir来获取文件
    {
             strcpy(s, rent->d_name);//获取文件名
        if (strlen(s) > maxlength) {maxlength = strlen(s);}
        if (s[0] != '.' && s)
        {
            res[cnt++]=s;
        }   
    }
    sort(res,res+cnt,cmp);//排序输出文件
    int num = 0;
    int breadth = size.ws_col / maxlength;
    while (num < cnt) {
        if (cnt / breadth == 0) {
            cout<<res[num]<<" ";
            num += 1;
        } else {
            for (int i = 0; i <= cnt / breadth; i++) {
                for (int j = 0; j < breadth; j++) {
                cout<<res[j * (cnt / breadth) + j + i ] <<" ";
                num += 1;
                if (num == cnt) continue;
        }
        cout<<"\n";
                }
            }
    }       
    closedir(dir);
}          
        

int main(int argc, char *argv[]) {
    char *if_ls;
    int swich;
    if (argc >=3) {
    for (int i = 1; i < argc; i++ ) {
        swich = 0;
        if_ls = argv[i]; 
        if (if_ls[0] == '-') swich = 1;
        switch(swich) {
            case 0 : break;
            case 1 : printf_ls_al(argc, argv[i+1]); break;
        }
    }
    } else {
        if_ls = argv[1];
        if(if_ls[0] == '-') {
            printf_ls_al(argc,argv[1]);
        } else{
            printf_ls(argc, argv[1]);
        }
    }
    return 0;
}
