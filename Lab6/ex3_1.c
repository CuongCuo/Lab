#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
// so sanh 3 va 3_1, thu tu thuc hien cua cha khi ko cho con 

int main(void){
  int status;
  pid_t pid = fork();
  
  if (pid < 0 ){
    perror("fork");
    return 1;
  }
  if (pid == 0){ // tien tring con
    printf("Toi la con\n");
    return 0;
  }
  /* Tiến trình cha: chờ con kết thúc */
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

  printf("Toi la cha cha cha\n"); // ko cho con 
  return 0;
}
