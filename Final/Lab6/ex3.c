#include <stdio.h>
#include <unistd.h>
// để tiến trình cha chờ tiến trình con ta dùng hàm waitpid()
int main() {
    int status;
    pid_t pid = fork();
    if(pid<0){
        perror("fork");
        exit(1);
    }
    else if (pid == 0){
        // con
        printf("PID: %d\n",getpid());
        exit(0);
    }
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }
  printf("Toi la cha cha cha\n"); // ko cho con 
  return 0;
}
