#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/stat.h>
/*
Bài 3: Kích thước và quyền truy cập của file
Viết chương trình nhập tên một file và in ra kích thước của file, thông tin chế độ truy cập
(access mode) của file. (Gợi ý: có thể dùng stat hoặc fstat): Hàm stat() trả về 1 struct stat, 
struct này chứa đựng các thông tin của file như: kích thước file, thời gian tạo file,
quyền truy cập của file,....
Nguyên văn: Write a program to enter the name of a file and print out the size of the file, the
access mode information of the file. (Hint: you can use stat or fstat
*/
#define size 256


int main(){
    char name[size];
    struct stat st;

    printf("Nhap ten file: \n");
    fgets(name,size,stdin);
    name[strcspn(name,"\n")] = '\0';

    if(stat(name,&st)) exit(1);
    printf("Kich thuoc file: %d bytes\n", st.st_size);
    printf("Che do truy cap: %o\n", st.st_mode);

    return 0;
}