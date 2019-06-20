/*************************************************************************
	> File Name: 3home.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年04月27日 星期六 18时00分12秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    struct stat *buf = malloc(sizeof(struct stat));
    struct dirent *readdir = malloc(sizeof(struct dirent));
    DIR *opendir(const char *name);
    if (stat(argv[1], buf) == -1) {
        perror("stat");
    }

    printf("%s",readdir(opendir("/home/liujunming/haizei/3.SystemProgramming/homework"))->d_name)
    
    printf("%s", readdir->d_name);
    printf("%d\t%d\t%d\t", buf->st_mode, buf->st_nlink, buf->st_size);
    


    return 0;
}
