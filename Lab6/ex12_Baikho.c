/*
 * Bài 12: Kết thúc có kiểm soát bằng SIGTERM.
 * Handler chỉ đặt cờ; luồng chính thoát khi cờ được đặt.
 */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static volatile sig_atomic_t stop = 0;

static void handle_sigterm(int signo)
{
    (void)signo;
    stop = 1;   /* chỉ đặt cờ, không gọi printf() trong handler */
}

int main(void)
{
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigterm;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("PID = %d\n", (int)getpid());
    fflush(stdout);

    while (!stop) {
        pause();    /* ngủ cho tới khi có tín hiệu */
    }

    printf("Clean shutdown\n");
    return 0;
}