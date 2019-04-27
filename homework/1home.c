/*************************************************************************
	> File Name: 1home.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年04月27日 星期六 09时33分46秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>

int main()
{   
    char computer[256];
    char *path = NULL;
    char str[100];
    char username[20];
    int true;
    struct utsname uts;
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    if (gethostname(computer, 255) != 0 || uname(&uts) < 0){
         fprintf(stderr, "Could not get host information \n"); 
         return 1;
   }
    path = getcwd(NULL,0);
    strncpy(username, pwd->pw_name, strlen(pwd->pw_name));
    if (username[0] == 'r' && username[1] == 'o' && username[2] == 'o' && username[3] == 't') {
    printf("\n\033[36m%s@%s:%s\033[0m#", pwd->pw_name, computer, path);
    } else {
    printf("\n\033[36m%s@%s:%s\033[0m$", pwd->pw_name, computer, path);
    }
    
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
    path = getcwd(NULL,0);
            if (username[0] == 'r' && username[1] == 'o' && username[2] == 'o' && username[3] == 't') {
                printf("\033[36m%s@%s:%s\033[0m#", pwd->pw_name, computer, path);
            } else {
                    printf("\033[36m%s@%s:%s\033[0m$", pwd->pw_name, computer, path);
            }
        } 
    memset(str , 0, strlen(str));
    }
    return 0;
}
