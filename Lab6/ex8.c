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
    execlp("not_a_command","not_a_command",(char *)NULL);
    perror("execlp");
    _exit(127); // command not found
  }

  /* Tiến trình cha: chờ con kết thúc */
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }
    if (WIFEXITED(status)) {
        printf("con = %d\n", WEXITSTATUS(status));
    } else {
        printf("con bi mo coi :))))");
    }

    return 0;
}
