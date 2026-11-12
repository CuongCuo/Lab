#include<stdio.h>
#include<string.h>
#include<unistd.h>
// ham pipe: vi du ghi va doc lai trong cung tien trin
// fd 1 la ghi, fd 2 la doc
int main(){
    int fd[2]; // gom 2 gia tri 01
    char buf[64];
    const char *msg = "Hello nigga"

    // goi pipe ra truoc fork() bang pipe(fd)
    if(pipe(fd)== -1){
        perror("pipe");
        return 1;
    }
    // ham ghi bao gom (arr[i], char, len(char))
    if(write(fd[1],msg, strlen(msg) == -1 )){ 
        perror("write");
        return 1;
    }
    // ham doc read(arr[i],buf,sizeof(buf)-1)
    if(read(fd[0],buf,sizeof(buf)-1)){
        perror("read");
        return 1;
    }
    buf[n] = '\0';
    printf("Received: %s\n", buf);
    close(fd[0]); // ngat ket noi doc
    close(fd[1]); // ngat ket noi ghi
    return 0;
}