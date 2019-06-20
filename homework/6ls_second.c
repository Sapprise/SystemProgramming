/*************************************************************************
	> File Name: 6ls_second.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年05月08日 星期三 22时45分35秒
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <algorithm>
#include <string.h>
#include <string>
using namespace std;

bool cmp(string s1, string s2)
{
    return s1<s2;
}

int main()
{
    //struct _dirstream typedef struct _dirstream DTR;
    char s[100];
    string res[1000];
    DIR *dir;
    struct dirent *rent;//struct
    dir = opendir("..");
    int cnt=0;
    while((rent=readdir(dir)))//利用dirent中的readdir来获取文件
    {
        strcpy(s,rent->d_name);//获取文件名
        if (s[0]!='.' && s)
        {
            res[cnt++]=s;
        }   
    }
    sort(res,res+cnt,cmp);//排序输出文件
    for(int i=0; i<cnt; i++)
        cout<<res[i]<<"  ";
    puts("");
    closedir(dir);
    return 0;
}

