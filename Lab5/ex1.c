/*
 Hello.txt
Cho file Hello.txt có nội dung: "Hello! What is your name?". Viết chương trình:
a) Đọc nội dung file Hello.txt và in ra màn hình.
b) Đọc nội dung file Hello.txt bắt đầu từ byte thứ 7 tính từ đầu file và in ra màn hình.
(Gợi ý: dùng system call lseek)
*/
// read all file contents
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    char str[512];
    // cau a
    FILE* ptr; // khai báo một con trỏ kiểu file
    ptr = fopen("Hello.txt", "r");
    if (ptr == NULL) exit(1);  // hàm xử lý nếu lỗi
    
    if ((fgets(str ,512,ptr))!=NULL){
        puts(str); // xuat chuoi ra man hinh
    }
    fclose(ptr);

    // cau b
    int fd = open("Hello.txt", O_RDONLY);
    if(fd == -1) exit(1);

    lseek(fd,7,SEEK_SET);
    int n = read(fd,str,512);
    if (n > 0) str[n] = '\0';
    puts(str);
    close(fd);

    return 0;


    

}