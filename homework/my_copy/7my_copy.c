/*************************************************************************
	> File Name: 7my_copy.c
	> Author: liujunming 
	> Mail: 1292917361@qq.com 
	> Created Time: 2019年05月10日 星期五 19时38分49秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define BUF_SIZE 1024
#define PATH_LEN 128
 
void my_err(char *err_string, int line )
{
    fprintf(stderr,"line:%d ",line);
    perror(err_string); 
    exit(1);
}
 
void copy_data(const int frd,const int fwd)
{
    int read_len = 0, write_len = 0;
    unsigned char buf[BUF_SIZE], *p_buf;
 
    while ( (read_len = read(frd,buf,BUF_SIZE)) ) {
         
        if (-1 == read_len) {
            my_err("Read error", __LINE__);
        }
        else if (read_len > 0) { //把读取部分写入目标文件
            p_buf = buf;
            while ( (write_len = write(fwd,p_buf,read_len)) ) {
                if(write_len == read_len) {
                    break;
                }
                else if (write_len > 0) { //只写入部分
                    p_buf += write_len;
                    read_len -= write_len;
                }
                else if(-1 == write_len) {
                    my_err("Write error", __LINE__);
                }
            }
            if (-1 == write_len) break;
        }
    }
}
 
//void copy_dir(char *src_dir, char *dest_dir) {
//    DIR *dp = NULL;
//    struct dirent *dirp;
//    char tempDest[256];
//    char tempSrc[256];
//    strcpy(tempDest, dest_dir);
//    strcpy(tempSrc, src_dir);
//    printf("dir\n");
//    /*使用opendir函数打开src_dir目录，获得指向该目录名字的指针*/
//    if ((dp = opendir(src_dir)) == NULL)
//        return 1;
//    else
//    {    
//        /*使用readdir函数读取dp所指代目录的目录项，获得指向下一个dirent结构的指针*/
//            while ((dirp = readdir(dp)))
//        {
//                    struct stat file_stat;
//                                /*将dirent结构中的d_name成员变量链接到上级目录字符串*/
//                                strcat(tempDest, dirp->d_name);
//                                strcat(tempSrc, dirp->d_name);
//                    
//                                /*此处转换为文件复制函数的方式处理目录复制*/
//                                copy_data(tempSrc, tempDest);
//                    
//                                /*通过字符串拷贝函数，将tempDest和tempSrc还原为上级的目录名*/
//                                            strcpy(tempDest, dest_dir);
//                                strcpy(tempSrc, src_dir);
//                
//        }
//         /*关闭目录*/
//             closedir(dp);
//    }
//}

int main(int argc, char *argv[]) 
{
     
    int frd, fwd; //读写文件描述符
    int len = 0;
    char *pSrc, *pDes; //分别指向源文件路径和目标文件路径
    struct stat src_st,des_st;
     
    if (argc < 3) {
        printf("用法 ./MyCp <源文件路径> <目标文件路径>\n");
        my_err("arguments error ", __LINE__);
    }
     
    frd = open(argv[1],O_RDONLY);
    if (frd == -1) {
        my_err("Can not opne file", __LINE__);
    }
 
    if (fstat(frd,&src_st) == -1) {
        my_err("stat error",__LINE__);
    }
    /*检查源文件路径是否是目录*/
    if (S_ISDIR(src_st.st_mode)) {
        my_err("略过目录",__LINE__);
      //  copy_dir(argv[1], argv[2]);
    }
     
    pDes = argv[2];
    stat(argv[2],&des_st);
    if (S_ISDIR(des_st.st_mode)) { //目标路径是目录，则使用源文件的文件名
         
        len = strlen(argv[1]);
        pSrc = argv[1] + (len-1); //指向最后一个字符
        /*先找出源文件的文件名*/
        while (pSrc >= argv[1] && *pSrc != '/') {
            pSrc--;
        }
        pSrc++;//指向源文件名
         
        len = strlen(argv[2]); 
        // . 表示复制到当前工作目录
        if (1 == len && '.' == *(argv[2])) {
            len = 0; //没有申请空间，后面就不用释放
            pDes = pSrc;
        }
        else { //复制到某目录下，使用源文件名
            pDes = (char *)malloc(sizeof(char)*PATH_LEN);
            if (NULL == pDes) {
                my_err("malloc error ", __LINE__);
            }
             
            strcpy(pDes,argv[2]);
         
            if ( *(pDes+(len-1)) != '/' ) { //目录缺少最后的'/'，则补上’/‘
                strcat(pDes,"/");
            }
            strcat(pDes+len,pSrc);
        }
    }
     
    /* 打开目标文件， 使权限与源文件相同*/ 
    fwd = open(pDes,O_WRONLY | O_CREAT | O_TRUNC,src_st.st_mode);
    if (fwd == -1) {
        my_err("Can not creat file", __LINE__);
    }
    copy_data(frd,fwd);
    //puts("end of copy");
    if (len > 0 && pDes != NULL)
        free(pDes);
     
    close(frd);
    close(fwd);
 
    return 0;
}
