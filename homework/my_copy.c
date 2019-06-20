/*************************************************************************
	> File Name: my_copy.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年05月10日 星期五 22时52分21秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_FILE 1024
#define PATH_LEN 128

void error(char *err_string, int line) {
    fprintf(stderr, "line:%d ", line);
    perror(err_string);
    exit(1);
}

void cp_date(int rd, int wd) {
    int flag;
    int read_len = 0, write_len = 0;
    char buf[SIZE_FILE];
    while ((flag = read(rd, buf, SIZE_FILE)) > 0) {
        write(wd, buf, flag);
    }
    printf("cp success\n");
    close(rd);
    close(wd);
}

char *if_dir(char *read, char *write) {
    struct stat st;
    char *psrc, *pdes;
    int len = 0;
    pdes = write;
    stat(write, &st);
    if (S_ISDIR(st.st_mode)) {
        len = strlen(read);
        psrc = read + len - 1;
        while (psrc >= read && *psrc != '/') {
            psrc--;
        }
        psrc++;
        len = strlen(write);
        if (len == 1 && *write == '.') {
            len = 0;
            pdes = psrc;
        } else {
            pdes = (char *) malloc(sizeof(char) *PATH_LEN);
            if (pdes == NULL) {
                error("malloc error ", __LINE__);
            }
            strcpy(pdes, write);
            if (*(pdes + len - 1) != '/') {
                strcat(pdes,"/");
            }
            strcat(pdes + len, psrc);
        }
    }
    return pdes;
}

int main(int argc, char *argv[]) {
    int frd, fwd;
    int len = 0;
    char *readp, *writep;
    struct stat src_st, des_st;

    if (argc < 3) {
        printf("输入有误！\n");
        error("argument error ", __LINE__);
    } else {
        for (int i = 1; i < argc - 1; i++) {
            frd = open(argv[i], O_RDONLY);
            fstat(frd, &src_st);
            if (S_ISDIR(src_st.st_mode)) {
                mkdir(if_dir(argv[i], argv[argc - 1]), 0755);
            } else {
                fwd = open(if_dir(argv[i], argv[argc - 1]), O_WRONLY | O_CREAT | O_TRUNC, src_st.st_mode);
                cp_date(frd, fwd);
            }
            printf("%s\n", if_dir(argv[i], argv[argc - 1]));
        }
    }
    return 0;
}
