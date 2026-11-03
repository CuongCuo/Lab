#include <stdio.h>
#include <unistd.h>
#define ALIVE_SEC 10
int main(void){
  printf("Pid= %ld\n",(long)getpid());
  printf("PPid= %ld\n",(long)getppid());

  fflush(stdout); // in khi gap Pipe

  unsignedlef left = ALIVE_SEC; // cha ghi cho bien nay
  while (left>0) {
    left = sleep(left);
  }
  return 0;
}
