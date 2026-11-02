// lý thuyết
/*
lệnh nằm trong thư viện <unistd.h> , <fcntl.h>
các hàm chính:
open
close
read
write
lseek : tìm kiếm nhị phân
các flags cần có đi kèm: O_RDONLY (doc), O_WRONLY (ghi), O_RDWR (đọc ghi) , 
*/
#include<unistd.h> // open, close
#include<fcntl.h> // for flags
#include<stdio.h>

int main(){
    int retval;
    int fd = open("Hello.txt", O_RDWR|O_CREAT, 0666); // 0666 là quyền truy cập
    if(fd == -1){
        perror("open"); // lệnh perror là lệnh in ra lỗi sai vào cửa sổ lỗi stderr
        
        return 1;
    }
    if ((retval = write(fd, "Hello", 5)) == -1){
        perror("write");
        return 1;
    }
    if((retval = close(fd)) == -1){
        perror("close");
        return 1;
    }
    return 0;
}