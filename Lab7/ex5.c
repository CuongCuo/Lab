/*
Bài 5. Trao đổi hai chiều bằng hai pipe
Yêu cầu
Viết chương trình C bai5.c để tiến trình cha và tiến trình con trao đổi thông điệp theo hai hướng
bằng hai pipe.
1. Tạo p2c[2] để truyền dữ liệu từ cha sang con và c2p[2] để truyền dữ liệu từ con sang cha.
2. Tiến trình cha gửi chuỗi Hello child qua p2c.
3. Tiến trình con đọc thông điệp, in ra màn hình rồi gửi lại chuỗi Hello parent qua c2p.
4. Tiến trình cha đọc và in thông điệp trả lời.
5. Mỗi tiến trình phải đóng tất cả đầu pipe không sử dụng ngay sau fork().
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int p2c[2];   /* cha -> con */
    int c2p[2];   /* con -> cha */
    pid_t pid;
    char buf[100];
    ssize_t n;

    if (pipe(p2c) == -1) {
        perror("pipe p2c");
        return 1;
    }
    if (pipe(c2p) == -1) {
        perror("pipe c2p");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        /* ===== Tiến trình con ===== */
        close(p2c[1]);   /* con không ghi vào p2c */
        close(c2p[0]);   /* con không đọc từ c2p */

        n = read(p2c[0], buf, sizeof(buf) - 1);
        if (n < 0) {
            perror("child read");
            return 1;
        }
        buf[n] = '\0';
        printf("Con nhận: %s\n", buf);
        close(p2c[0]);

        const char *reply = "Hello parent";
        if (write(c2p[1], reply, strlen(reply)) < 0) {
            perror("child write");
            return 1;
        }
        close(c2p[1]);
        return 0;
    }

    /* ===== Tiến trình cha ===== */
    close(p2c[0]);   /* cha không đọc từ p2c */
    close(c2p[1]);   /* cha không ghi vào c2p */

    const char *msg = "Hello child";
    if (write(p2c[1], msg, strlen(msg)) < 0) {
        perror("parent write");
        return 1;
    }
    close(p2c[1]);

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