/*
 * Mở rộng 2: Chờ không chặn với WNOHANG.
 * Cha kiểm tra con mỗi giây mà không bị chặn.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int status;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {                  /* con ngủ 5 giây rồi kết thúc */
        sleep(5);
        _exit(0);
    }

    for (;;) {
        pid_t r = waitpid(pid, &status, WNOHANG);

        if (r == -1) {
            perror("waitpid");
            return 1;
        }

        if (r == 0) {                /* con chưa kết thúc */
            printf("Child is still running\n");
            fflush(stdout);
            sleep(1);
            continue;
        }

        /* r == pid: con đã kết thúc */
        if (WIFEXITED(status))
            printf("Child exited with code %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("Child killed by signal %d\n", WTERMSIG(status));
        break;
    }

    return 0;
}