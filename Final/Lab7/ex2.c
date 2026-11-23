/*
Yêu cầu
Viết chương trình C bai2.c để tiến trình cha gửi một chuỗi cho tiến trình con qua pipe.
1. Gọi pipe() trước khi gọi fork().
2. Trong tiến trình cha, đóng đầu đọc, ghi chuỗi Message from parent vào pipe rồi đóng đầu ghi.
3. Trong tiến trình con, đóng đầu ghi, đọc dữ liệu từ pipe và in ra màn hình.
4. Tiến trình cha dùng waitpid() để chờ tiến trình con kết thúc.
5. Kiểm tra lỗi của pipe(), fork(), read() và write()
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
    int fd[2];
    char buf[256];
    int status;


    if(pipe(fd)==-1){
        perror("pipe");
        exit(1);
    }
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        return 1;
    }
    if(pid == 0){
        close(fd[1]);
        ssize_t n = read(fd[0],buf,sizeof(buf)-1);
        if(n<0){
            perror("read");
            close(fd[0]);
            _exit(1);
        }
        buf[n] = '\0';
        printf("Child nhan: %s\n",buf);
        close(fd[0]);
        _exit(0);
    }
    // cha
    close(fd[0]);
    const char *msg = "Message from parent";
    size_t len = strlen(msg);
    
    if(write(fd[1], msg, len) != (ssize_t) len){
        perror("write");
        close(fd[1]);
        waitpid(pid, &status, 0);
        return 1;
    }
    close(fd[1]);

    if(waitpid(pid,&status,0)==-1){
        perror("waitpid");
        return 1;
    }
    return 0;
}