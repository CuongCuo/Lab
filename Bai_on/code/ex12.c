#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define CMDSIZ 128

void process_command(char *cmdbuf) {
    // Tách chuỗi lệnh thành mảng args
    char *args[32];
    int i = 0;
    char *tok = strtok(cmdbuf, " \t");
    while (tok != NULL && i < 31) {
        args[i++] = tok;
        tok = strtok(NULL, " \t");
    }
    args[i] = NULL;
    if (args[0] == NULL) return; // Dòng trống

    // Lệnh cd phải chạy ở tiến trình cha
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] && chdir(args[1]) == -1) perror("cd");
        return;
    }

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return; }

    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        _exit(127);
    } else {
        waitpid(pid, NULL, 0);
    }
}

int main(void) {
    int logout = 0;
    ssize_t cmdsiz;
    char cmdbuf[CMDSIZ];

    while (!logout) {
        write(1, "myshell> ", 9);
        cmdsiz = read(0, cmdbuf, CMDSIZ - 1);
        if (cmdsiz <= 0) break;
        cmdbuf[cmdsiz - 1] = '\0';

        if (strcmp("logout", cmdbuf) == 0)
            ++logout;
        else
            process_command(cmdbuf);
    }
    return 0;
}
