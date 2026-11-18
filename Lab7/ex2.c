/*
Bài 2. Cha gửi dữ liệu cho con
Yêu cầu
Viết chương trình C bai2.c để tiến trình cha gửi một chuỗi cho tiến trình con qua pipe.
1. Gọi pipe() trước khi gọi fork().
2. Trong tiến trình cha, đóng đầu đọc, ghi chuỗi Message from parent vào pipe rồi đóng đầu ghi.
3. Trong tiến trình con, đóng đầu ghi, đọc dữ liệu từ pipe và in ra màn hình.
4. Tiến trình cha dùng waitpid() để chờ tiến trình con kết thúc.
5. Kiểm tra lỗi của pipe(), fork(), read() và write().
Kết quả
Ví dụ
Child received: Message from parent
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void){
    int fd[2];
    char buf[64];
    const char *msg = "Message from parent";

    if(pipe(fd)==-1){
        perror("pipe");
        return 1;
    } // tien trinh con
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        close(fd[0]);
        close(fd[1]);

        return 1;
    } 
    // con đóng f1, cha đóng f0
    if(pid == 0){
        close(fd[1]);
        if(read(fd[0],buf,sizeof(buf)-1)==-1){
            perror("read");
            close(fd[0]);
            _exit(127);
        }
        printf("Child received: %s\n", buf);

        close(fd[0]); // Đọc xong, đóng đầu đọc
        _exit(0);
    }
    // tiến trình cha
    close(fd[0]); // Đóng đầu đọc không dùng đến
    if(write(fd[1],msg, strlen(msg)==-1)){
        perror("write");
    }
    close(fd[1]);
    waitpid(pid,NULL,0);
    return 0;
}
