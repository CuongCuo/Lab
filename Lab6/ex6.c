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
  if (pid == 0){ // tien tring con
    _exit(7);
  }
  /* Tiến trình cha: chờ con kết thúc */
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }
    
    if(WIFEXITED(status)) printf("Con ok: %d", WIFEXITED(status));
    else printf("Oh hell nah");
    return 0;
}
