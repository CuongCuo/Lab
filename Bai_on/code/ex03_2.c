#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); return 1; }

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        // Con: chạy ls, đẩy stdout vào đầu ghi pipe
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("ls", "ls", NULL);
        perror("execlp ls");
        _exit(127);
    } else {
        // Cha: chạy grep ".txt", nhận stdin từ đầu đọc pipe
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execlp("grep", "grep", ".txt", NULL);
        perror("execlp grep");
        return 1;
    }
}
