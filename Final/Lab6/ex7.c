#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

/*Viết chương trình C bai7.c để tiến trình con thực thi lệnh ls -l bằng một hàm thuộc họ
exec.
1. Tạo tiến trình con bằng fork().
2. Trong tiến trình con, dùng execlp() hoặc execvp() để thực thi lệnh ls -l.
3. Nếu lời gọi exec thất bại, dùng perror() rồi kết thúc tiến trình con bằng _exit(127).
4. Tiến trình cha dùng waitpid() để chờ tiến trình con kết thúc.
Kết quả: Chương trình hiển thị kết quả tương tự khi chạy trực tiếp lệnh tương đương:*/

int main(){
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        return 1;
    }
    if(pid == 0){
        execlp("ls","ls","-l",NULL);
        perror("exec");
        _exit(127);
    }
    waitpid(pid,NULL,0);
    return 0;
}