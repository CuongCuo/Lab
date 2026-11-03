#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// so sanh 3 va 3_1, thu tu thuc hien cua cha khi ko cho con 

int main(void){
  pid_t pid = fork();
  
  if (pid < 0 ){
    perror("fork");
    return 1;
  }
  if (pid == 0){ // tien tring con
    printf("Toi la con\n");
    return 0;
  }
  printf("Toi la cha cha cha\n"); // ko cho con 
  return 0;
}
