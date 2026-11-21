/*
Viết chương trình C bai6.c để tiến trình cha nhận và giải mã trạng thái kết thúc của tiến
trình con.
1. Tiến trình con kết thúc bằng _exit(7).
2. Tiến trình cha gọi waitpid() để nhận biến status.
3. Dùng WIFEXITED(status) để kiểm tra tiến trình con có kết thúc bình thường hay không.
3
4. Dùng WEXITSTATUS(status) để in mã kết thúc của tiến trình con.*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
    pid_t pid = fork();
    int status;
    if(pid<0){
        perror("fork");
        return 1;
    }
    if(pid == 0){
        _exit(7);
    }
    if(waitpid(pid,&status,0)==-1){
        perror("waitpid");
        return 1;
    }
    if(WIFEXITED(status)) printf("Con thoat voi: %d\n",WEXITSTATUS(status));
    return 0;
}