/*************************************************************************
	> File Name: ls.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年05月11日 星期六 15时10分37秒
 ************************************************************************/

#include <stdio.h>
#include <stdilb.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <pwd.h>

int ls_opt = 0;
char work_dir[256]

void do_ls(char *dirname) {
    printf()
}

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "al")) != -1) {
        switch (opt) {
            case 'a' :
            ls_opt++;
                break;
            case 'l' :
                ls_opt += 2;
                break;
            default:
                exit(1);
        }
    }
    argc -= (optind - 1);
    argv += (optind - 1);
    if (argc == 1) {
        do_ls(",");
    } else {
        while(--argc) {
            do_ls(*(++argv));
        }
    }
    return 0;
}

