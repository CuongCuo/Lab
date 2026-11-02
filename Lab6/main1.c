#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
// ham execvp("ls",argv) : thay chuong trinh dang chay thanh 1 chuonhg trinh khac

int main(){
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  }
  if (pid == 0){
    char *argv[] = {"-ls","-l","NULL"}
    execvp(argv[0],argv); // thay the toan bo khong gian bang bin\ls 
    perror("execvp");
    _exit(127); // thoat chuong trinh con ma ko anh huong den chuong trinh chay
    }
waitpid(pid,NULL,0); // waitpid(pid, &status, 0) co block
}
