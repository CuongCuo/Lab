#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/*
Yêu cầu
Viết chương trình C bai1.c để tạo một pipe và truyền một chuỗi trong cùng một tiến trình.
1. Tạo pipe bằng pipe(fd) và kiểm tra lỗi.
2. Ghi chuỗi Hello pipe vào fd[1] bằng write().
3. Đọc dữ liệu từ fd[0] bằng read().
4. Thêm ký tự '\0' vào cuối dữ liệu đọc được và in chuỗi ra màn hình.
5. Đóng cả hai đầu pipe trước khi kết thúc chương trình.
*/
int main(){
    int fd[2]; // co 2 gia , -1
    char buf[64];
    const char *msg= "Hello pipe";
    if(pipe(fd)==-1){
        perror("pipe");
        return 1;
    }
    if(write(fd[1],msg,strlen(msg))==-1){
        perror("write");
        retunr 1;
    }
    if(read(fd[0],buf,sizeof(buf)-1)){
        perror("read");
        return 1;
    }
    printf("Received: %s\n",buf);
    close(fd[0]);
    close(fd[1]);
    return 0;
}