/*
Bài 8. Thu đầu ra của lệnh bằng pipe
Yêu cầu
Viết chương trình C bai8.c để tiến trình cha nhận đầu ra của lệnh uname -a được thực thi trong
tiến trình con.
1. Tạo pipe trước khi gọi fork().
2. Trong tiến trình con, chuyển STDOUT_FILENO sang đầu ghi của pipe bằng dup2().
3. Đóng các đầu pipe không còn sử dụng trong tiến trình con.
4. Dùng execlp() hoặc execvp() để chạy uname -a.
5. Trong tiến trình cha, đóng đầu ghi, đọc dữ liệu từ đầu đọc của pipe và in ra màn hình với tiền tố
Captured:.
6. Tiến trình cha gọi waitpid() để thu thập tiến trình con
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
int main(void){
    int fd[2];
    char buf[1024];
    if(pipe(fd)==-1){
        perror("pipe");
        return 1;
    }
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        return 1;
    }
    if(pid == 0){
        // con
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        close(fd[1]);
        execlp("uname","uname","-a",NULL);
        perror("exec");
        _exit(1);
    }
    // cha
    close(fd[1]);
    ssize_t n = read(fd[0],buf,sizeof(buf)-1);
    if(n == -1){
        perror("read");
        close(fd[0]);
        return 1;
    }
    buf[n] = '\0';
    printf("Captured: %s\n",buf);
    close(fd[0]);
    // cha goi waitpid
    waitpid(pid,NULL,0);
    return 0;
}