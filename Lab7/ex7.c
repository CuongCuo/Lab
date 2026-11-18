/*
Bài 7. Chuyển hướng stdin từ tệp
Yêu cầu
Viết chương trình C bai7.c sử dụng dup2() để chương trình đọc đầu vào chuẩn từ tệp input.txt
đã chuẩn bị ở đầu tài liệu.
1. Mở input.txt bằng open() với cờ O_RDONLY.
2. Gọi dup2(fd, STDIN_FILENO) rồi đóng fd gốc.
3. Dùng read(STDIN_FILENO, ...) hoặc fgets() để đọc dữ liệu từ đầu vào chuẩn.
4. In dữ liệu đọc được ra màn hình và giải thích vì sao chương trình không cần đọc trực tiếp từ file
descriptor trả về bởi open() nữa.
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
int main(){
    char buf[64];
    int fd = open("input.txt", O_RDONLY);
    if(fd == -1){
        perror("open");
        return 1;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    ssize_t n = read(STDIN_FILENO, buf, sizeof(buf)-1);
    if(n == -1){
        perror("read");
        return 1;
    }
    // in ra man hih
    buf[n] ='\0';
    printf("data: %s\n",buf);
    return 0;
}