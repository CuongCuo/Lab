/*
Viết chương trình linuxmkdir.c mô phỏng lệnh shell mkdir. Chương trình nhận 1 tham số
đầu vào: đường dẫn thư mục cần tạo trong argv[1]. (Gợi ý: dùng system call mkdir
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
    if (mkdir(argv[1]) != 0) {   // dung mkdir()
        perror("mkdir");
        exit(1);
    }
    printf("Created directory: %s\n", argv[1]);
    return 0;
}