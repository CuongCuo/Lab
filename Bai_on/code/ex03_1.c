#include <stdio.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("Con (PID=%d, PPID=%d) dang chay...\n", getpid(), getppid());
        sleep(2);
        printf("Con ket thuc (PPID hien tai=%d).\n", getppid());
    } else {
        // Cha KHÔNG gọi wait() -> kết thúc ngay
        printf("Cha (PID=%d) da tao con (PID=%d) va khong cho.\n", getpid(), pid);
    }
    return 0;
}
