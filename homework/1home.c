/*************************************************************************
	> File Name: homework.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年04月14日 星期日 19时26分09秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/utsname.h>
int main(void)
{   
    char computer[256];
    char *path = NULL;
    struct utsname uts;
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    if(gethostname(computer, 255) != 0 || uname(&uts) < 0){
         fprintf(stderr, "Could not get host information \n"); 
         return 1;
   }
    path = getcwd(NULL,0);
    printf("\033[47;36m%s@%s:%s\033[0m\n", pwd->pw_name,computer,path );
    return 0;
}
