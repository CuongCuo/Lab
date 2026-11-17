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
static int execute_external(const Command *cmd){
    pid_t pid= fork();
    if(pid<0){
        perror("minish: fork");
        return -1;
    }
    if (pid==0){
    /* ĐÂY LÀ TIẾN TRÌNH CON */
    /* Thực hiện execvp() tại đây */
    execvp(cmd->argv[0],cmd->argv);
    perror("minish: execvp");
    _exit(127);
    }
    // Tiến trình cha chờ waitpid()
    int status;
    pid_t res;
    while (waitpid(pid, &status, 0) == -1 && errno == EINTR);  /* bị ngắt bởi tín hiệu thì đợi tiếp */
    return 0;
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
        
        // in ket qua M2
        execute_external(&cmd);
    }
    free(line);
    return 0;
}
