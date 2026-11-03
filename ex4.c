#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static int idata = 1000;

int main(void){
  int istack =150;
  int status;
  pid_t pid = fork();
 
  if (pid < 0) {          /* Lỗi */
        perror("fork");
        return 1;
    }
  if(pid == 0){ //tien trinh con 
    idata = 2000;
    istack = 3000;
    printf("Child : idata = %d, istack = %d\n", idata, istack);
    return 0;
  }
  if (waitpid(pid,&status,0)==-1){ // cho con in ra roi in
    perror("waitpid");
    return 1;
  }
  printf("Parent: idata = %d, istack = %d\n", idata, istack);
  return 0;
}
