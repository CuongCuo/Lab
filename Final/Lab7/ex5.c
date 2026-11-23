#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int fd[2];
    char buf[256];
    int p2c[2]; int c2p[2];
    pid_t pid = fork();
    ssize_t n;

    if (pipe(p2c) == -1) {
        perror("pipe p2c");
        return 1;
    }
    if (pipe(c2p) == -1) {
        perror("pipe c2p");
        return 1;
    }
    if(pid < 0){
        perror("fork");
        return 1;
    }
    if(pid == 0){
        // con
        close(p2c[1]);
        close(c2p[0]);
        n = read(p2c[0], buf, sizeof(buf) - 1);
         if (n < 0) {
            perror("child read");
            return 1;
        }
        buf[n] ='\0';
        printf("con nhan: %s\n",buf);
        close(c2p[1]);
        return(0);
    }
    // cha
    close(p2c[0]);   /* cha không đọc từ p2c */
    close(c2p[1]);   /* cha không ghi vào c2p */
    const char *msg = "Hello child";
    if(write(c2p[1],msg,strlen(msg))<0){
        perror("write"); return 1;
    } close(p2c[1]);
    n = read(c2p[0], buf, sizeof(buf) - 1);
    if (n < 0) {
        perror("parent read");
        return 1;
    }
    buf[n] = '\0';
    printf("Cha nhận: %s\n", buf);
    close(c2p[0]);
    wait(NULL);

    return 0;
}