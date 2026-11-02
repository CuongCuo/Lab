/*
iết chương trình linuxrmdir.c mô phỏng lệnh shell rmdir. Chương trình nhận 1 tham số
đầu vào: đường dẫn thư mục (rỗng) cần xoá trong argv[1]. (Gợi ý: dùng system call rmdir)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/stat.h>    /* mkdir() */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);
    }
    if (rmdir(argv[1]) != 0) {   // dung rmdir()
        perror("rmdir");
        exit(1);
    }
    printf("Deleted directory: %s\n", argv[1]);
    return 0;
}