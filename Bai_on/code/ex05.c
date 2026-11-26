#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd = open("Hello.txt", O_RDONLY);
    if (fd == -1) { perror("open Hello.txt"); return 1; }

    char buf[256];
    ssize_t n;

    // a) Đọc toàn bộ nội dung file
    printf("a) Toan bo file:\n");
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        write(STDOUT_FILENO, buf, n);
    }
    printf("\n");

    // b) Đọc từ byte thứ 7 tính từ đầu file (offset = 7)
    if (lseek(fd, 7, SEEK_SET) == -1) { perror("lseek"); close(fd); return 1; }
    printf("b) Tu byte thu 7:\n");
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        write(STDOUT_FILENO, buf, n);
    }
    printf("\n");

    close(fd);
    return 0;
}
