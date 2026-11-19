/*
Chương trình 2 – Process
1. Tạo tiến trình con bằng fork().
2. Tiến trình con gán shared_var = 10, in giá trị rồi kết thúc.
3. Tiến trình cha chờ tiến trình con bằng waitpid() rồi in shared_var.
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int shared_var = 0;
int main(){
    int fd[2];
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
    }
// tien trinh con
    if(pid == 0){
        shared_var = 10;
        printf("con sharevar: %d\n",shared_var);
        return 0;
    }
// tien trinh cha
    waitpid(pid,NULL,0);
    printf("Tien trinh cha: shared_var = %d\n", shared_var);
    return 0;
}