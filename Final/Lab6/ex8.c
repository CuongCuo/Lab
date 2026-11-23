#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
/*
Viết chương trình C bai8.c để chủ động tạo trường hợp execvp() thất bại và kiểm tra cách
xử lý lỗi.
1. Tạo tiến trình con bằng fork().
2. Trong tiến trình con, gọi execvp() với một tên chương trình không tồn tại, ví dụ
not_a_command.
3. Ngay sau execvp(), gọi perror("execvp") rồi _exit(127).
4. Tiến trình cha dùng waitpid() và in mã kết thúc của con.
5. Giải thích vì sao đoạn mã sau execvp() chỉ chạy khi lời gọi này thất bại.
Kết quả cần quan sát: Tiến trình con báo lỗi từ execvp(), còn tiến trình cha nhận được
mã kết thúc 127*/

int main(){
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        return 1;
    }
    if(pid == 0){
        execvp("null","null","-nigga",NULL); // con ko ton tai 
        perror("execvp");
        _exit(127);
    }
    if(waitpid(pid,NULL,0)==-1){
        perror("waitpid");
        return 1;
    } 
    if (WIFEXITED(status)) {
        printf("con = %d\n", WEXITSTATUS(status));
    }
    return 0;
}