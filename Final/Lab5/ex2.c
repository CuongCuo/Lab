/*
Viết chương trình tạo một file với hai lựa chọn:
 Chọn 1: Nội dung của file được nhập từ bàn phím.
 Chọn 2: Đọc nội dung của một file khác và ghi vào file vừa tạo*/
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    int choice;
    int fd;
    char buf[1024];
    char dest[256], src[256];
    ssize_t n;


    printf("chon 1 trong 2:\n1.Nhap tu ban phim\n2.Ghi de\n");
    scanf("%d", &choice);
    getchar(); // xoa ky tu \n sau scanf

    printf("Nhap ten file dich: \n");
    fgets(dest,sizeof(dest),stdin);
    dest[strcspn(dest,"\n")]='\0';

    fd = open(dest,O_WRONLY|O_CREAT|O_TRUNC,0644);
    if(fd<0){perror("open");exit(1);}

    if(choice == 1){
        printf("Nhap noi dung file: \n");
        while(fgets(buf,sizeof(buf),stdin) && strcspn(buf,'\n') != 0){
            write(fd,buf,strlen(buf));
        }
    }else{
        printf("Nhap ten file nguon: \n");
        fgets(src,sizeof(src),stdin);
        src[strcspn(src,"\n")] = '\0';
        int fd_src = open(src, O_RDONLY);
        if (fd_src < 0) exit(1);

        while(n = read(fd_src,buf,sizeof(buf))>0){ // các tham số file descriptor, bộ đệm, kích thước tối đa
            write(fd,buf,n); // các tham số file descriptor, bộ đệm, số byte thực tế 
        }
        close(fd_src);
        printf("Xong");
    }
    close(fd);
    return 0;


}