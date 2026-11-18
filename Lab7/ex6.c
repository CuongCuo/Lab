/*
Viết chương trình C bai6.c sử dụng dup2() để chuyển hướng đầu ra chuẩn vào tệp output.txt.
1. Mở output.txt với các cờ O_WRONLY | O_CREAT | O_TRUNC và quyền 0644.
2. Gọi dup2(fd, STDOUT_FILENO).
3. Đóng fd gốc sau khi dup2() thành công.
2/5
LẬP TRÌNH HỆ THỐNG LAB 7 – BÀI TẬP
4. Dùng printf() để in hai dòng bất kỳ.
5. Sau khi chương trình kết thúc, dùng cat output.txt để kiểm tra kết quả
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(){
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        perror("open");
        return 1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    printf("Day di ong chau oi\n");
    printf("Hello world\n");
    return 0;
}