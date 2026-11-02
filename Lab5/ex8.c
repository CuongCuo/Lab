/*
Bài 8: linuxcd.c
Viết chương trình linuxcd.c mô phỏng lệnh shell cd. Chương trình nhận 1 tham số đầu vào:
đường dẫn thư mục trong argv[1]. (Gợi ý: dùng system call chdir)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   /* chdir() */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);
    }

    if (chdir(argv[1]) != 0) {
        perror("chdir");
        exit(1);
    }

    printf("Changed directory to: %s\n", argv[1]);
    return 0;
}