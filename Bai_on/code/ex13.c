#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int p2c[2], c2p[2]; // 2 pipe: cha->con và con->cha
    if (pipe(p2c) == -1 || pipe(c2p) == -1) { perror("pipe"); return 1; }

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        // Tiến trình con
        close(p2c[1]);
        close(c2p[0]);

        const char *msg_to_parent = "Hello parent";
        write(c2p[1], msg_to_parent, strlen(msg_to_parent) + 1);

        char buf[128];
        read(p2c[0], buf, sizeof(buf));
        printf("[Con] Nhan tu cha: %s\n", buf);

        close(p2c[0]);
        close(c2p[1]);
    } else {
        // Tiến trình cha
        close(p2c[0]);
        close(c2p[1]);

        const char *msg_to_child = "Hello children";
        write(p2c[1], msg_to_child, strlen(msg_to_child) + 1);

        char buf[128];
        read(c2p[0], buf, sizeof(buf));
        printf("[Cha] Nhan tu con: %s\n", buf);

        close(p2c[1]);
        close(c2p[0]);
        wait(NULL);
    }
    return 0;
}
