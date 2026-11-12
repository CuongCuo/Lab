// dup 2: làm fd mới tahm chiếu tới fd cũ, nếu đang mở thì đóng fd đó tránh nhân bản
// trong thư viện unistd.h
// int dup2(int oldfd, int newfd)
// ví dụ pipeline 2 tiến trình
/*
tạo pipe 
tạo process 1
dùng dup2(fd[1],STDOUT_FILENO)
đóng 2 file, gọi execlp cho ls

tạo process 2
dup2(fd[0], STDIN_FILENO)
đóng file gốc
gọi lệnh 2 qua execlp

2 con gọi exec
cha đóng cả 2 và chờ con
*/
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void){
    int fd[2];
    if(pipe(fd)==-1){
        perror("pipe");
        return 1;
    }
    pid_t p1 = fork();
    if(p1 == -1){
        perror("fork");
        return 1;
    }
    if(p1 == 0){
        if(dup2(fd[1],STDOUT_FILENO)== -1){
            perror("dup2");
            _exit(1);
        }
        close(fd[0]);
        close(fd[1]);
        execlp("ls","ls",(char*)NULL);
        perror("execlp");
        _exit(127);
    }
    pid_t p2 = fork();
    if(p2 == -1){
        perror("fork");
        return 1;
    }
    if(p2 == 0){
        if(dup2(fd[0],STDIN_FILENO) == -1){
            perror("dup2");
            _exit(1);
        }
        close(fd[0]);
        close(fd[1]);
        execlp("wc","wc","l",(char*)NULL);
        perror("execlp");
        _exit(127);
    }
    close(fd[0]);
    close(fd[1]);
    // PID CHO 2 TIEN TRINH
    waitpid(p1,NULL,0);
    waitpid(p2,NULL,0);
    return 0;
}
