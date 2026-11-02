#include <stdio.h>
#include <unistd.h>

int main(){
    char buf[512];
    int fd; // file decriptor
    int nbytes; // so bytes doc

    if ((nbytes = write(1, "Hello World!\n", 12))<0){
        perror("write");
        exit(1); // in ra stderr rồi exit
    }

    fd = open("Hello.txt", O_RDONLY);
    if((nbytes = read(fd, buf, sizeof(buf)))<0){
        perror("read");
        exit(1); // in ra stderr rồi exit
    }

    if(close(fd) == -1){
        perror("close");
        exit(1);
    }

    printf("Read %d bytes: %s\n", nbytes, buf);

    return 0;
}