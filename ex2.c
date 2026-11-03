// tao tien trinh con voi fork()
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
  pid_t pid = fork(); // tra ve -1, 0:CON , >0: CHA dang cay 
  if (pid < 0){
    perror("fork");
    return 1;
  }
  if (pid == 0){
    printf("Con: PID = %ld PPID = %ld\n", (long)getpid(),(long)getppid());
  } else {
    printf("Cha: PID = %ld PPID = %ld\n", (long)getpid(),(long)getppid());
  }
  return 0;
}
