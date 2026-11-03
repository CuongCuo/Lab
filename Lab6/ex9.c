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
    _exit(0);
  }

  /* Tiến trình cha: in pid con va ngu */
  printf("Pid con la: %d\n", (int)pid);
  fflush(stdout);
  sleep(20);
  // ngat khi zombie qua lau di a
  if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }
    return 0;
}
