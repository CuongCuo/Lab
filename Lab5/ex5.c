#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        exit(1);
    }

    char *pattern  = argv[1];
    char *filename = argv[2];

    /* Mở file chỉ đọc */
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    char buf[BUF];       
    char line[BUF];      
    int  line_pos = 0;   
    int  n;
    /*
     * Đọc file theo từng khối (chunk).
     * Với mỗi byte đọc được, ghép vào 'line' cho đến khi
     * gặp '\n' hoặc hết file → kiểm tra pattern rồi in.
     */
    while ((n = read(fd, buf, BUF)) > 0) {
        for (int i = 0; i < n; i++) {
            char c = buf[i];

            if (c == '\n' || line_pos == BUF - 1) {
                /* Kết thúc dòng: thêm null-terminator */
                line[line_pos] = '\0';
                /* Nếu dòng chứa pattern thì in ra */
                if (strstr(line, pattern) != NULL) {
                    printf("%s\n", line);
                }
                /* Reset cho dòng tiếp theo */
                line_pos = 0;
            } else {
                line[line_pos++] = c;
            }
        }
    }
    /* Xử lý dòng cuối cùng nếu file không kết thúc bằng '\n' */
    if (line_pos > 0) {
        line[line_pos] = '\0';
        if (strstr(line, pattern) != NULL) {
            printf("%s\n", line);
        }
    }

    if (n < 0) {
        perror("read");
        close(fd);
        exit(1);
    }
    close(fd);
    return 0;
}
