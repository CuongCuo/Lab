#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        const char *home = getenv("HOME");
        execlp("ls", "ls", "-la", home ? home : ".", NULL);
        perror("execlp");
        _exit(127);
    } else {
        wait(NULL);
    }
    return 0;
}
