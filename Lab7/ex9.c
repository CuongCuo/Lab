/*
Bài 9. Xây dựng pipeline ls | wc -l
Viết chương trình C bai9.c để mô phỏng pipeline ls | wc -l mà không gọi shell.
1. Tạo một pipe và hai tiến trình con.
2. Tiến trình con thứ nhất chuyển stdout sang đầu ghi của pipe rồi chạy ls bằng exec.
3. Tiến trình con thứ hai chuyển stdin sang đầu đọc của pipe rồi chạy wc -l bằng exec.
4. Tiến trình cha đóng cả hai đầu pipe ngay sau khi tạo xong hai tiến trình con.
5. Tiến trình cha dùng waitpid() để chờ cả hai tiến trình con.
6. So sánh kết quả với khi chạy ls | wc -l trong shell.
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd[2];
    pid_t pid1, pid2;

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    /* Con thứ nhất: ls */
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        _exit(1);
    }
    if (pid1 == 0) {
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            _exit(1);
        }
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", (char *)NULL);
        perror("execlp ls");
        _exit(127);
    }

    /* Con thứ hai: wc -l */
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        _exit(1);
    }
    if (pid2 == 0) {
        if (dup2(fd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            _exit(1);
        }
        close(fd[0]);
        close(fd[1]);   
        execlp("wc", "wc", "-l", (char *)NULL);
        perror("execlp wc");
        _exit(127);
    }

    /* Cha: đóng cả hai đầu pipe */
    close(fd[0]);
    close(fd[1]);

    /* Cha: chờ cả hai con */
    if (waitpid(pid1, NULL, 0) == -1) {
        perror("waitpid ls");
    }
    if (waitpid(pid2, NULL, 0) == -1) {
        perror("waitpid wc");
    }
    return 0;
}