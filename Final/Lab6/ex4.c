#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
static int data = 1000;

int main() {
    int istack = 150;
    pid_t pid = fork();
    if(pid<0){
        perror("fork");
        exit(1);
    }
    else if (pid == 0){
        data = 2000;
        istack = 2000;
        printf("data: %d\nistack: %d\n",data,istack);
        exit(1);
    }
    // cha
    if(waitpid(pid,NULL,0) == -1){
        perror("waitpid");
        exit(1);
    } else{
        printf("data: %d\nistack: %d\n",data,istack);
    }
    return 0;
}