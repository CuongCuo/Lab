#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
/*
Bài 3. Con gửi dữ liệu cho cha
Yêu cầu
Viết chương trình C bai3.c để tiến trình con gửi một chuỗi cho tiến trình cha qua pipe.
1. Gọi pipe() trước fork().
2. Trong tiến trình con, đóng đầu đọc, ghi chuỗi Hello parent rồi đóng đầu ghi.
3. Trong tiến trình cha, đóng đầu ghi, đọc dữ liệu từ pipe và in ra màn hình.
4. Tiến trình cha gọi waitpid() trước khi kết thúc.*/
int main(){
    int fd[2];
    char buf[1024];
    if(pipe(fd)==-1){perror("pipe");exit(0);}
    pid_t pid = fork();
    if(pid<0){perror("fork"); return 1;}
    if(pid == 0){
        close(fd[0]);
        const char *msg = "Hello parent";
        ssize_t n = write(fd[1],msg,strlen(msg));
        if(n<0){perror("write");exit(1);}
        close(fd[1]);
        exit(1);
    }

    // cha
    close(fd[1]);
    ssize_t n = read(fd[0],buf,sizeof(buf)-1);
    if(n<0){perror("read");exit(0);}
    else {
        buf[n]= '\0';
        printf("Parent nhan: %s\n",buf);
    }
    close(fd[0]);
    return 0;
}