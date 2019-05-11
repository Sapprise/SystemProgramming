/*************************************************************************
	> File Name: 1mk.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年05月11日 星期六 11时53分39秒
 ************************************************************************/

#include <stdio.h>
#include <sys/stat.h>

int main(char argc, char *argv[]) {
    int ok = 0;
    if ( (ok = mkdir(argv[1],0755)) != 0 ) {
    }
    return 0;
}
