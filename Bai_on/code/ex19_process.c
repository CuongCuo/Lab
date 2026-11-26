#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int sharedVar = 5; // Mỗi tiến trình có bản sao riêng

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        sharedVar = 20;
        printf("Child Process: sharedVar = %d\n", sharedVar);
        exit(0);
    } else {
        wait(NULL);
        // Kết quả: sharedVar vẫn là 5 vì cha và con có vùng nhớ tách biệt (Copy-on-Write)
        printf("Parent Process: sharedVar = %d\n", sharedVar);
    }
    return 0;
}
