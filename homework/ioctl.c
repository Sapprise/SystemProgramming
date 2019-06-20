/*************************************************************************
	> File Name: ioctl.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年05月08日 星期三 19时43分43秒
 ************************************************************************/

#include <stdio.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<termios.h>

int main()
{
    //定义winsize 结构体变量
    struct winsize size;
    //TIOCSWINSZ命令可以将此结构的新值存放到内核中
    ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
    int wscol = size.ws_col;
    printf("%d\n", wscol);
    printf("%d\n",size.ws_col);
    printf("%d\n",size.ws_row);
    return 0;
}
