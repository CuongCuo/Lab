/*
Bài 11. Truyền dữ liệu cảm biến qua FIFO
Yêu cầu
Viết hai chương trình C sensor.c và monitor.c mô phỏng việc truyền dữ liệu đo qua FIFO sensor.fifo.
1. Chương trình sensor.c: Lần lượt gửi ba dòng S1 -65 , S2 -70 , S3 -60 qua FIFO, mỗi dòng kết thúc bằng \n.
2. Chương trình monitor.c: Đọc dữ liệu từ FIFO cho đến EOF và ghi toàn bộ dữ liệu nhận được ra stdout.
3. Chương trình gửi phải đóng FIFO sau khi gửi xong để chương trình nhận có thể quan sát EOF.
4. Chạy hai chương trình ở hai terminal và kiểm tra thứ tự dữ liệu nhận được.

Kết quả mong đợi:
S1 -65
S2 -70
S3 -60

Cách dùng:
- Chạy 2 terminal riêng biệt:
    Terminal 1: ./ex11 monitor
    Terminal 2: ./ex11 sensor
- Hoặc chạy tự động 2 tiến trình: ./ex11
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define FIFO_NAME "sensor.fifo"

int run_sensor(void) {
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open sensor");
        return 1;
    }

    const char *lines[] = {
        "S1 -65\n",
        "S2 -70\n",
        "S3 -60\n"
    };
    int count = sizeof(lines) / sizeof(lines[0]);

    for (int i = 0; i < count; i++) {
        if (write(fd, lines[i], strlen(lines[i])) == -1) {
            perror("sensor write");
            close(fd);
            return 1;
        }
        usleep(100000); // Ngắt quãng nhẹ 100ms giữa các dòng
    }

    // Đóng FIFO để bên monitor nhận được EOF (read trả về 0)
    close(fd);
    return 0;
}

int run_monitor(void) {
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open monitor");
        return 1;
    }

    char buf[128];
    ssize_t n;
    // Đọc liên tục cho đến khi gặp EOF (n == 0)
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        if (write(STDOUT_FILENO, buf, n) == -1) {
            perror("write stdout");
            close(fd);
            return 1;
        }
    }

    if (n == -1) {
        perror("read monitor");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

int main(int argc, char *argv[]) {
    // Tự động tạo FIFO nếu chưa tồn tại
    if (mkfifo(FIFO_NAME, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    // Nếu chạy với đối số: ./ex11 monitor hoặc ./ex11 sensor
    if (argc > 1) {
        if (strcmp(argv[1], "monitor") == 0 || strcmp(argv[1], "read") == 0) {
            return run_monitor();
        } else if (strcmp(argv[1], "sensor") == 0 || strcmp(argv[1], "write") == 0) {
            return run_sensor();
        } else {
            fprintf(stderr, "Cách dùng:\n  %s monitor  (chạy monitor)\n  %s sensor   (chạy sensor)\n  %s          (chạy tự động cả hai)\n", 
                    argv[0], argv[0], argv[0]);
            return 1;
        }
    }

    // Nếu chạy không truyền đối số: Tự động fork 2 tiến trình (con làm sensor, cha làm monitor)
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Con: sensor
        sleep(1); // Chờ monitor mở file trước
        int ret = run_sensor();
        _exit(ret);
    } else {
        // Cha: monitor
        run_monitor();
        waitpid(pid, NULL, 0);
        unlink(FIFO_NAME); // Dọn dẹp FIFO
    }

    return 0;
}
