/* Bài 2: Tạo file với 2 lựa chọn - dùng system call POSIX */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF 1024

int main(void){
    int choice;
    char dest[256], src[256], buf[BUF]; // dest: ten file dich, src: file nguon, buf BUffer luu du lieu
    ssize_t n; // so byte doc dc

    printf("Nhap lua chon: \n1. Nhap tu ban phim\n2.Sao chep tu file nguon");
    scanf("%d", &choice);
    getchar(); // xoa ky tu \n sau scanf

    printf("Nhap ten file dich: ");
    fgets(dest,sizeof(dest),stdin);
    dest[strcspn(dest,"\n")] = '\0'; // xoa ky tu \n con lai 

    int fd = open(dest, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (fd < 0) exit(1);

    if (choice == 1){
        printf("Nhap noi dung (dong trong de ket thuc)\n")
        while(fgets(buf,BUF,stdin) && strcspn(buf,'\n') != 0){
            write(fd,buf,strlen(buf));
        }
    } else{
        printf("Nhap ten file nguon: ");
        fgets(src, sizeof(src), stdin);
        src[strcspn(src,'\n')] = '\0';
        int fd_src = open(src, O_RDONLY);
        if (fd_src < 0) exit(1);

        while(n = read(fd_src,buf,BUF)){ // các tham số file descriptor, bộ đệm, kích thước tối đa
            write(fd,buf,n); // các tham số file descriptor, bộ đệm, số byte thực tế 
        }
        close(fd_src);
        printf("Xong");
    }
    close(fd);
    return 0;
}
