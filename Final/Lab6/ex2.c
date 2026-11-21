/*
Viết chương trình C bai2.c sử dụng fork() để tạo một tiến trình con.
1. Kiểm tra đầy đủ ba trường hợp trả về của fork(): Lỗi, tiến trình con và tiến trình cha.
2. Trong tiến trình con, in PID và PPID của tiến trình con.
3. Trong tiến trình cha, in PID của tiến trình cha và PID của tiến trình con do fork() trả
về.
4. Chạy chương trình nhiều lần và quan sát thứ tự xuất hiện của hai dòng kết quả.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(1);
    } else if (pid == 0){
        // con
        printf("%d\n", getpid());
    } else printf("%d\n",getppid());
    return 0;
}