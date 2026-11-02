/*
Bài 3: Kích thước và quyền truy cập của file
Viết chương trình nhập tên một file và in ra kích thước của file, thông tin chế độ truy cập
(access mode) của file. (Gợi ý: có thể dùng stat hoặc fstat): Hàm stat() trả về 1 struct stat, 
struct này chứa đựng các thông tin của file như: kích thước file, thời gian tạo file,
quyền truy cập của file,....
Nguyên văn: Write a program to enter the name of a file and print out the size of the file, the
access mode information of the file. (Hint: you can use stat or fstat
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define SIZE 256

int main(void){
    char NAME_LEN[SIZE];
    struct stat info;

    printf("Nhap ten file: ");
    fgets(NAME_LEN, SIZE, stdin);
    NAME_LEN[strcspn(NAME_LEN, "\n")] = '\0';

    if(stat(NAME_LEN, &info)) exit(1);
    printf("Kich thuoc file: %d bytes\n", info.st_size);
    printf("Che do truy cap: %o\n", info.st_mode);

    return 0;
}
