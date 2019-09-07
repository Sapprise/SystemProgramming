/*************************************************************************
	> File Name: server.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年06月18日 星期二 13时08分18秒
 ************************************************************************/


#include <stdio.h>
#include <sys/types.h>   
#include <sys/socket.h>  
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 
 
int startup(const char* _ip, int _port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("----sock----fail\n");
		exit(-1);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(_ip);
	local.sin_port = htons(_port);
	if (bind(sock, (struct sockaddr*)&local, sizeof(local)) != 0) {
		perror("---bind---fail\n");
		close(sock);
		exit(-2);
	}
	if (listen(sock, 20) != 0) {
		perror("----listen----fail\n");
		close(sock);
		exit(-1);
	}
	return sock;		
}
 
int main()
{
    char ip_addr[20] = "192.168.2.93";
	int listen_sock = startup(ip_addr, 8888);
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
 
	char buf[1024];
	while(1) {
		int new_sock = accept(listen_sock,(struct sockaddr*)&client, &len);
		if (new_sock < 0) {
			perror("----accept----fail\n");
			close(listen_sock);
			exit(-5);
		}
		pid_t id = fork();
		if (id == 0) {
			close(listen_sock);
            FILE * fd;
            char *path;
            int name = 1;
			while(1) {
                memset(buf, '\0', sizeof(buf));
                if (name == 1) {
                    name += 1;
                    read(new_sock, buf, 10);
                    path = (char *)malloc(sizeof(char) * (sizeof(buf) + 1));
                    //printf("buf:%s\n", buf);
                    //strcpy(buf, "ad");
                    //printf("buf:%s\n", buf);
                    strncpy(path, buf, sizeof(buf));
                    //printf("path:%s\n", path);
                    fd = fopen(path, "w+");
                    free(path);
                } else {
			    int s = read(new_sock,buf, 1);
			        if(s > 0 )
			        {
			    	    printf("%s\n", buf);
                        fwrite(buf, s, 1,fd);
			        } else if( s == 0) {
					    printf("client quit. \n");
					    break;
				    } else break;
			    }
            }
            fclose(fd);
			exit(0);
 
		} else if (id > 0) {
			close(new_sock); 
			if (fork() > 0) {
				exit(0);
			}
		}
	}
	return 0;
}
