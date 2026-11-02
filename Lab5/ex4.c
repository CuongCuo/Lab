/*
Bài 4: linuxecho.c
Viết chương trình tên linuxecho.c mô phỏng lệnh:
echo [string] > example.txt
(Chuỗi cần in nằm trong argv[1], tên file nằm trong argv[2]
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF 1024
int main(int argc, char* argv[]){
    if(argc != 3){ // 3 tham số bao gồm tên chương trình, chuỗi cần ghi và tên file
        printf("Usage: %s [string] > [filename]\n", argv[0]);
        return 1;
    }
    char *text = argv[1]; // argv[1] là chuỗi cần ghi 
    char *filename = argv[2];   
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC ,0644); // mo file, neu chua co tao moi, neu co roi ghi de
    if(fd < 0) exit(1);

    write(fd, text, strlen(text)); // ghi chuoi vao file
    write(fd, "\n", 1); // them xuong dong cho giong echo
    close(fd);
    return 0;
}