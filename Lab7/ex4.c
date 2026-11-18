/*
Viết chương trình C bai4.c để quan sát điều kiện xuất hiện EOF trên pipe.
1. Tiến trình cha ghi lần lượt ba dòng packet 1, packet 2, packet 3 vào pipe.
2. Sau khi ghi xong, tiến trình cha đóng đầu ghi của pipe.
3. Tiến trình con đóng đầu ghi ngay sau fork() và gọi read() trong vòng lặp cho đến khi hàm trả
về 0.
4. Mỗi khối dữ liệu đọc được phải được ghi ra STDOUT_FILENO bằng write().
5. Sau vòng lặp, tiến trình con in thông báo EOF received.
Câu hỏi
Điều gì xảy ra nếu tiến trình cha không đóng fd[1] sau khi đã gửi xong dữ liệu?
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void){
    int fd[2];
    const char *msg1 = "packet 1\n";
    const char *msg2 = "packet 2\n";
    const char *msg3 = "packet 3\n";
    char buf[64];

    if(pipe(fd)==-1){
        perror("pipe");
        return 1;
    }
    // tiến trình cha ghi vào pipe, và đóng fd
    for(int i = 0; i < 3; i++){
        const char *msg;
        switch(i){
            case 0:
                msg = msg1;
                break;
            case 1:
                msg = msg2;
                break;
            case 2:
                msg = msg3;
                break;
        }
        if(write(fd[1],msg,strlen(msg))==-1){
            perror("write");
            close(fd[0]);
            return 1;
        }
    }
    // Tạo tiến trình con
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        close(fd[1]);
        return 1;
    }
    if(pid == 0){
        // dọc từ pipe
        close(fd[1]);
        if(n == -1){
            perror("read");
            close(fd[0]);
            _exit(1);
        }
        while ((n = read(fd[0], buf, sizeof(buf) - 1)) > 0){
            buf[n]='\0';
            write(STDOUT_FILENO,buf,n);
        }
        printf("EOF recieved\n");
        close(fd[0]);
        _exit(0);
    }
    // tiến trình cha đóng fd[1] sau khi ghi xong
    close(fd[0]);
    close(fd[1]);
    waitpid(pid,NULL,0);

    return 0;
}
