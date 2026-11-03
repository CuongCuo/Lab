#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
// doc vi tri cua fd sau fork 
int main(){
  int fd = open(Hello.txt, O_RODONLY);
  char buf[256];
  size_tn;
  int status;

  if(fd<0){
    perror("open");
    return 1;
  }
  pid_t pid = fork();
  if(pid <0){
    perror("fork");
    return 1;
  }
  if (pid == 0){
    if (lseek(fd,7,SEEK_SET)==-1){
      perror("lseek");
      _exit(1); // _exit cho con
    }
    _exit(0);
  }

  
}
