#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){
  int status;
  pid_t pid = fork();
  
  if (pid < 0 ){
    perror("fork");
    return 1;
  }
  if (pid > 0){ // tien tring con
    printf("Cha =%d, con= %d",(int)getpid, (int),getpid )
    fflush(stdout);
    return 0;
  }
    printf("Child: PPID ban dau = %d\n", (int)getppid());
    fflush(stdout);
 
    sleep(3);
    
    printf("Child: PPID sau 3 giay = %d\n", (int)getppid());
    fflush(stdout);

    return 0;
}
