#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
    printf("Before");          
    fflush(stdout);            
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf(" (child)\n");
        return 0;              
    }

    printf(" (parent)\n");
    waitpid(pid, NULL, 0);
    return 0;
}