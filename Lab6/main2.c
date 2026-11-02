#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
int main(){
  pid_t pid = fork();
  int status;
  waitpid(pid, &status,0);
  if(WIFEXITED(status)){ // KIEM TRA XEM CO KET THUC BINH THUONG HAY KO 
    printf("ma thoat = %d\n", WEXITSTATUS(status));
  } else if (WIFSIGNALED(status)) {
    printf("BI TIN HIEU SO");
  }
  return 0;
}
