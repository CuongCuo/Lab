/*
Bài 3. Con gửi dữ liệu cho cha
Yêu cầu
Viết chương trình C bai3.c để tiến trình con gửi một chuỗi cho tiến trình cha qua pipe.
1. Gọi pipe() trước fork().
2. Trong tiến trình con, đóng đầu đọc, ghi chuỗi Hello parent rồi đóng đầu ghi.
3. Trong tiến trình cha, đóng đầu ghi, đọc dữ liệu từ pipe và in ra màn hình.
4. Tiến trình cha gọi waitpid() trước khi kết thúc.
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void){
    int fd[2];
    char buf[64];
    const char *msg = "Hello parent";

    if(pipe(fd)==-1){
        perror("pipe");
        return 1;
    } // tien trinh con
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        return 1;
    } 
    // con đóng f1, cha đóng f0
    if(pid == 0){
        close(fd[0]); // đóng đầu đọc
        if(write(fd[1],msg, strlen(msg))==-1){
        perror("write");
        _exit(1);
    }
        close(fd[1]); // Đọc xong, đóng đầu đọc
        _exit(0);
    }
    // tiến trình cha
    close(fd[1]); // Đóng đầu ghi
    ssize_t n = read(fd[0], buf, sizeof(buf) - 1);
    if (n == -1) {
        perror("read");
    } else {
        buf[n] = '\0';
        printf("Parent received: %s\n", buf);
    }
    close(fd[0]);
    waitpid(pid,NULL,0);
    return 0;
}

