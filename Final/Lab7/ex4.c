#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include<stdlib.h>

int main(void){
    int fd[2];
    
    char buf[1024];

    if(pipe(fd)==-1){perror("pipe"); return 1;}
    pid_t pid = fork();
    if(pid == -1){perror("fork");close(fd[1]);return 1;}
    if(pid == 0){
        close(fd[1]);
        ssize_t n;
        while((n= read(fd[0],buf,sizeof(buf)-1))>0){
            buf[n]='\0';
            // ghi du lieu ra stdout
            write(STDOUT_FILENO,buf,n);
        }
        printf("EOF recieved");
        close(fd[0]);
        exit(0);
    }
    // cha
    close(fd[0]);

    const char *msg1 = "packet 1\n";
    const char *msg2 = "packet 2\n";
    const char *msg3 = "packet 3\n";

    write(fd[1], msg1, strlen(msg1));
    write(fd[1], msg2, strlen(msg2));
    write(fd[1], msg3, strlen(msg3));
    close(fd[1]);
    waitpid(pid,NULL,0);
    return 0;
}