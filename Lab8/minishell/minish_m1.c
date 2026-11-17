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

#define MAX_ARGS  32
#define MAX_LINE  4096
/*
các bước M1:
1: Hiển thị prompt
2: đọc lệnh
3: kiểm tra độ dài
4: tokenizer
5: in kết quả
6: dọn dẹp
*/
typedef struct {
    char *argv[MAX_ARGS + 1]; // +1 for NULL terminator
    int argc;
} Command;
// nhận một chuỗi line và lưu vào struct cmd,mảng agrv
static int parse_command(char *line, Command *cmd) {
    // Implementation for parsing command
    // xóa struct 
    memset (cmd,0,sizeof(Command));
    char *saveptr = NULL;
    char *tok = strtok_r(line, " \t\r\n", &saveptr);
    while (tok!= NULL){
        if(cmd->argc >= MAX_ARGS){
            fprintf(stderr,"minish: qua nhieu doi so\n");
            return -1;
        }
        // thêm token vào mảng ảgv
        cmd->argv[cmd->argc] = tok;
        cmd->argc++;
        cmd->argv[cmd->argc]=NULL; // cho toi khi bang null
        tok = strtok_r(NULL, " \t\r\n", &saveptr);// lay token tiep theo
    }
    if(cmd->argc>0) return 1; //co dong
    return 0; // dong trong
}

int main(void){
    
    // cho dung luong va dong
    char *line = NULL;
    ssize_t capacity = 0;

    while (1){
        fputs("minish> ",stdout);
        fflush(stdout);
        // doc lenh bang getline
        ssize_t len = getline(&line,&capacity,stdin);
        if(len == -1) break;
        if(len > MAX_LINE){
            fprintf(stderr,"minish: dai vai qua roi\n");
            continue;
        }
        Command cmd;
        int result = parse_command(line,&cmd);
        if(result == 0) continue; 
        if(result == -1) continue;
        
        // in ket qua M1
        printf("argc: %d\n",cmd.argc);
        for (int i = 0; i < cmd.argc; i++){
            printf("argv[%d]=\"%s\"\n", i, cmd.argv[i]);}
    }
    free(line);
    return 0;
}
