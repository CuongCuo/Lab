#include <stdio.h>    /* fputs, fflush, getline, fprintf, printf, perror */
#include <stdlib.h>   /* free, getenv */
#include <string.h>   /* strtok_r, memset, strlen */
#include <stdbool.h>  /* bool (dùng từ M3) */
/* M2+ */
#include <unistd.h>   /* fork, execvp, chdir, _exit, dup2, close, pipe */
#include <sys/types.h>/* pid_t */
#include <sys/wait.h> /* waitpid */
#include <fcntl.h>    /* open, O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC */
#include <errno.h>    /* errno, EINTR */

/*
các bước M1:
1: Hiển thị prompt
2: đọc lệnh
3: kiểm tra độ dài
4: tokenizer
5: in kết quả
6: dọn dẹp
*/
int main(void){
    
    // cho dung luong va dong
    char *line = NULL;
    ssize_t capacity = 0;

    while (1){
        fputs("minish> ",stdout);
        fflush("stdout");
        // doc lenh bang getline
        ssize_t = getline(&line,&capacity,stdin);
        if(len == -1) break;
        if(len > MAX_LINE){
            fprintf(stderr,"minish: dai vai qua roi\n");
            continue;
        }

    }
}
