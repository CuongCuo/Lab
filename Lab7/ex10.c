/*
Bài 10. Tạo FIFO và truyền dữ liệu giữa hai chương trình
Yêu cầu
Viết hai chương trình C reader.c và writer.c trao đổi dữ liệu qua FIFO data.fifo.
1. Tạo FIFO bằng lệnh mkfifo data.fifo trước khi chạy hai chương trình.
2. Chương trình reader.c: Mở FIFO bằng O_RDONLY, đọc một chuỗi rồi in ra màn hình.
3. Chương trình writer.c: Mở FIFO bằng O_WRONLY, ghi chuỗi Hello from writer rồi đóng FIFO.
4. Chạy reader và writer ở hai terminal khác nhau.
5. Đổi thứ tự khởi chạy hai chương trình và quan sát hành vi tại lời gọi open().
6. Sau khi thực hành, xóa FIFO bằng rm -f data.fifo.

Kết quả mong đợi:
Received: Hello from writer

Cách dùng:
- Chạy 2 terminal riêng biệt:
    Terminal 1: ./ex10 reader
    Terminal 2: ./ex10 writer
- Hoặc chạy tự động 2 tiến trình: ./ex10
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

#define FIFO_NAME "data.fifo"

int run_reader(void) {
    printf("[Reader] Đang mở FIFO để đọc (chờ writer nếu chưa mở)...\n");
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open reader");
        return 1;
    }

    char buf[128];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if (n == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    buf[n] = '\0';
    printf("Received: %s\n", buf);
    close(fd);
    return 0;
}

int run_writer(void) {
    printf("[Writer] Đang mở FIFO để ghi (chờ reader nếu chưa mở)...\n");
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open writer");
        return 1;
    }

    const char *msg = "Hello from writer";
    if (write(fd, msg, strlen(msg)) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("[Writer] Đã gửi thông điệp và đóng FIFO.\n");
    close(fd);
    return 0;
}

int main(int argc, char *argv[]) {
    // Tự động tạo FIFO nếu chưa tồn tại
    if (mkfifo(FIFO_NAME, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    // Nếu chạy với đối số: ./ex10 reader hoặc ./ex10 writer
    if (argc > 1) {
        if (strcmp(argv[1], "reader") == 0 || strcmp(argv[1], "read") == 0) {
            return run_reader();
        } else if (strcmp(argv[1], "writer") == 0 || strcmp(argv[1], "write") == 0) {
            return run_writer();
        } else {
            fprintf(stderr, "Cách dùng:\n  %s reader  (chạy reader)\n  %s writer  (chạy writer)\n  %s         (chạy tự động cả hai)\n", 
                    argv[0], argv[0], argv[0]);
            return 1;
        }
    }

    // Nếu chạy không truyền đối số: Tự động fork 2 tiến trình (cha làm reader, con làm writer)
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Tiến trình con đóng vai trò writer
        sleep(1); // Chờ reader mở trước một chút để minh họa
        int ret = run_writer();
        _exit(ret);
    } else {
        // Tiến trình cha đóng vai trò reader
        run_reader();
        waitpid(pid, NULL, 0);
        unlink(FIFO_NAME); // Xóa FIFO sau khi hoàn tất
    }

    return 0;
}
