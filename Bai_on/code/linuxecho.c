#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Cach dung: %s <chuoi> <ten_file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) { perror("open"); return 1; }

    write(fd, argv[1], strlen(argv[1]));
    write(fd, "\n", 1);
    close(fd);
    return 0;
}
