#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

int socket_connect (char *host, int port) {
	int sockfd;
	struct sockaddr_in dest_addr;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket() error");
        return -1;  
	}

	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port);
	dest_addr.sin_addr.s_addr = inet_addr(host);

	//DBG("Connetion TO %s:%d\n",host,port);
	//fflush(stdout);
	if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
		//perror("connect() error");
		//DBG("connect() error : %s!\n", stderror(errno));
		return -1;
	}
	return sockfd;

}

int main(int argc, char *argv[]) {
	int  socket_fd;
    FILE * fd;
	struct passwd *pwd;
    pwd = getpwuid(getuid());	
	char ip_addr[20] = "192.168.2.93";
	int port = 8888;
    char username[20] = {0};
    strcpy(username, pwd->pw_name);
	socket_fd = socket_connect(ip_addr, port);
    if (socket_fd > 0) {
     printf("success!\n");
}
    int sread = 1;
    int name = 1;
    char buf[1024];
    fd = fopen(argv[1],"rw");
    while(sread != 0) {
        memset(buf, '\0', sizeof(buf));
        if (name == 1) {
            strcpy(buf, argv[1]);
            write(socket_fd, buf, 10);
            name += 1;
        } else {
            sread = fread(buf, 1, 1, fd); 
            if (sread > 0) {
                write(socket_fd, buf, strlen(buf));
            }
        } 
    }
        fclose(fd);
	    close(socket_fd);
	return 0;
}


