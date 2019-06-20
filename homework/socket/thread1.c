/*************************************************************************
	> File Name: thread1.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年06月20日 星期四 13时38分57秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>

int higt,weight;
void sca() {
    scanf("%d", &higt);
    scanf("%d", &weight);
}

void prin() {
    printf("%d\n", higt);
    printf("%d\n", weight);
}

int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, (void *)&sca, NULL);
    pthread_join(thread1, NULL);
    pthread_create(&thread2, NULL, (void *)&prin, NULL);
    pthread_join(thread2, NULL);
    return 0;
}
