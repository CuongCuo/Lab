/*
Given file Hello.txt with content: "Hello! What is your name?". Write a program
to: 
a) Read the content of file Hello.txt and print on the screen. 
b) Read the content of file Hello.txt
starting from the 7th byte from the beginning of the file and print on the screen. (Hint: using lseek
system call)
*/
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main(){
    int fd = open("Hello.txt",O_RDONLY);
    char buf[1024];
    
    ssize_t n ;
    if(fd<0){exit(1);}
    
    lseek(fd,0,SEEK_SET);
    n = read(fd,buf,sizeof(buf)-1);
    
    buf[n]='\0';
    puts(buf);
    close(fd);
    return 0;
}