/*************************************************************************
	> File Name: use_sititimer.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年07月11日 星期四 19时17分42秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

struct itimerval itime;
void init_time() {

    itime.it_value.tv_sec = 0;
    itime.it_value.tv_usec = 200000;

    itime.it_interval.tv_sec = 2;
    itime.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &itime, NULL);
    
    while(1);
}

void output() {
    printf("Hello World\n");
    itime.it_value.tv_sec += 1;
    setitimer(ITIMER_REAL, &itime, NULL);
}

void init_sig() {
    struct sigaction act;
}

int main() {
    signal(SIGALRM, output);
    init_time();
    while(1);
    return 0;

}
