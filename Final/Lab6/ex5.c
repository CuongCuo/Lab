/*
Viết chương trình C bai5.c để kiểm tra sự thay đổi vị trí đọc của tệp khi file descriptor được
kế thừa qua fork().
1. Mở Hello.txt bằng open() với cờ O_RDONLY trước khi gọi fork().
2. Trong tiến trình con, dùng lseek(fd, 7, SEEK_SET) để thay đổi vị trí đọc rồi kết thúc.
3. Tiến trình cha dùng waitpid() chờ con kết thúc.
4. Tiến trình cha dùng chính fd đã mở trước fork() để đọc phần còn lại của tệp và in ra
màn hình.
5. Giải thích vì sao tiến trình cha bắt đầu đọc từ vị trí mà tiến trình con đã đặt.
Kết quả: Với nội dung chuẩn bị ở đầu tài liệu, phần tiến trình cha đọc được bắt đầu từ ký tự*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
    // mở file
    int fd = open("Hello.txt", O_RDONLY);
    char buf[256];
    ssize_t n;
    int status;

    if(fd<0){
        perror("open");
        return 1;
    }
    pid_t pid = fork();
    if(pid<0){
        perror("fork");
        return 1;
    }
    if(pid == 0){
        if(lseek(fd,7,SEEK_SET)==-1){
            perror("lseek");
            _exit(1);
        }
        _exit(0);
    }
    if(waitpid(pid,&status,0)==-1){
        perror("waitpid");
        close(fd);
        return 1;
    }
    printf("Phan con lai cua tep la: \n");
    fflush(stdout);

    while((n = read(fd,buf,sizeof(buf)))>0){
        if(write(STDOUT_FILENO,buf,n)!=n){
            perror("write");
            break;
        }
    }
    if(n<0) perror("read");
    printf('\n');
    close(fd);
    return 0;

}