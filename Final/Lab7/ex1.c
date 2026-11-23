/*
Viết chương trình C bai1.c để tạo một pipe và truyền một chuỗi trong cùng một tiến trình.
1. Tạo pipe bằng pipe(fd) và kiểm tra lỗi.
2. Ghi chuỗi "Hello pipe" vào fd[1] bằng write().
3. Đọc dữ liệu từ fd[0] bằng read().
4. Thêm ký tự '\0' vào cuối dữ liệu đọc được và in chuỗi ra màn hình.
5. Đóng cả hai đầu pipe trước khi kết thúc chương trình.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int fd[2];

    // 1. Tạo pipe
    if(pipe(fd) == -1){
        perror("pipe");
        exit(1);
    }

    // 2. Ghi chuỗi vào đầu ghi fd[1]
    const char *msg = "Hello form pipe";
    ssize_t len = strlen(msg);
    if(write(fd[1],msg,len)!= (ssize_t)len){
        perror("write");
        close(fd[1]);
        close(fd[0]);
        exit(1);
    }

    // 3. Đọc dữ liệu từ đầu đọc fd[0]
    char buf[256];
    ssize_t n = read(fd[0],buf,sizeof(buf)-1);
    if(n < 0){
        perror("read");
        close(fd[1]);
        close(fd[0]);
        exit(1);
    }

    // 4. Thêm '\0' rồi in chuỗi
    buf[n] = '\0';
    printf("%s\n", buf);

    // 5. Đóng cả hai đầu pipe
    close(fd[0]);
    close(fd[1]);
    return 0;
}