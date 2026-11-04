/*
 * Bài 11: Xử lý SIGINT (Ctrl+C) và kết thúc có kiểm soát.
 * Handler chỉ đặt cờ; phần còn lại xử lý trong luồng chính.
 */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static volatile sig_atomic_t stop = 0;

static void handle_sigint(int signo)
{
    (void)signo;
    stop = 1;   /* chỉ đặt cờ, không gọi printf() trong handler */
}

int main(void)
{
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("PID = %d\n", (int)getpid());
    fflush(stdout);

    while (!stop) {
        pause();    /* ngủ cho tới khi có tín hiệu */
    }

    printf("SIGINT received, exiting\n");
    return 0;
}