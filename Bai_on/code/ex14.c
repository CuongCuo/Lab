#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); return 1; }

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        // Con: chạy ls, chuyển stdout -> fd[1]
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("ls", "ls", NULL);
        perror("execlp ls");
        _exit(127);
    } else {
        // Cha: chạy wc -l, chuyển stdin <- fd[0]
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        return 1;
    }
}
