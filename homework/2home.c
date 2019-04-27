/*************************************************************************
	> File Name: 2home.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年04月27日 星期六 09时29分50秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <signal.h>

int main()
{   
    char computer[256];
    char buffer[100];
    char user[] = "/home/liujunming";
    char str[100];
    char username[20];
    int true;
    struct utsname uts;
    struct passwd *pwd;
    signal(SIGINT, SIG_IGN);
    pwd = getpwuid(getuid());
    if (gethostname(computer, 255) != 0 || uname(&uts) < 0){
         fprintf(stderr, "Could not get host information \n"); 
         return 1;
   }
    getcwd(buffer,sizeof(buffer));
    strncpy(username, pwd->pw_name, strlen(pwd->pw_name));
    if (username[0] == 'r' && username[1] == 'o' && username[2] == 'o' && username[3] == 't') {
        if (strlen(buffer) >= strlen(user)) {
    printf("\n\033[36m%s@%s:~%s\033[0m#", pwd->pw_name, computer, buffer+16);
        } else {
    printf("\n\033[36m%s@%s:%s\033[0m#", pwd->pw_name, computer, buffer);
        }
    } else {
        if (strlen(buffer) >= strlen(user)) {
    printf("\n\033[36m%s@%s:~%s\033[0m$", pwd->pw_name, computer, buffer+16);
        } else {
    printf("\n\033[36m%s@%s:%s\033[0m$", pwd->pw_name, computer, buffer);
        }
    }
   memset(buffer, 0, strlen(buffer));
    while (1) {
    scanf("%s", str);
    getchar();
        if(str[0] == 'e' && str[1] == 'x' && str[2] == 'i' && str[3] == 't') {
            break;
        }
        if (str[0] == 'c' && str[1] == 'd') {
            continue;
        } else {
   
    true = chdir(str);
        if(true != 0) {
            printf("输入有误，请重新输入。\n");
    }
            
    pwd = getpwuid(getuid());
    if (gethostname(computer, 255) != 0 || uname(&uts) < 0){
         fprintf(stderr, "Could not get host information \n"); 
         return 1;
   }
     getcwd(buffer, sizeof(buffer));
            if (username[0] == 'r' && username[1] == 'o' && username[2] == 'o' && username[3] == 't') {
        if (strlen(buffer) >= strlen(user)) {
    printf("\n\033[36m%s@%s:~%s\033[0m#", pwd->pw_name, computer, buffer+16);
        } else {
    printf("\n\033[36m%s@%s:%s\033[0m#", pwd->pw_name, computer, buffer);
        }
            } else {
        if (strlen(buffer) >= strlen(user)) {
    printf("\n\033[36m%s@%s:~%s\033[0m$", pwd->pw_name, computer, buffer+16);
        } else {
    printf("\n\033[36m%s@%s:%s\033[0m$", pwd->pw_name, computer, buffer);
        }
            }
        } 
    memset(buffer, 0, strlen(buffer));
    memset(str , 0, strlen(str));
    }
    return 0;
}
