// Pipe giao tiếp giữa tiến trình cha và con
/*
 * Các bước thực hiện:
 * 1. Tạo pipe: pipe(fd) -> fd[0] để đọc (read end), fd[1] để ghi (write end).
 * 2. Tạo tiến trình con bằng fork() -> Cả cha và con đều kế thừa fd[0], fd[1]
 *    (tham chiếu cùng buffer trong kernel).
 * 3. Mỗi tiến trình đóng đầu pipe không sử dụng (con đóng fd[1], cha đóng fd[0]).
 * 4. Tiến trình ghi dùng write(), tiến trình đọc dùng read().
 * 5. Đóng các đầu pipe còn lại sau khi hoàn thành và cha đợi con kết thúc.
 */
 /*
 Giả sử cha chỉ ghi và con chỉ đọc: cha là 1, con là 0
- Tiến trình cha: Đóng fd[0] vì không đọc.
- Tiến trình con: Đóng fd[1] vì không ghi.
- Tiến trình cha: Đóng fd[1] sau khi gửi xong dữ liệu.
4/12
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 64

int main(void) {
    int fd[2];

    // 1. Tạo pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // 2. Phân nhánh tiến trình
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        close(fd[0]); // đóng vì nó chứa copy fd[0], fd[1]
        close(fd[1]);
        return 1;
    }

    if (pid == 0) {
        // --- TIẾN TRÌNH CON (Đọc dữ liệu) ---
        close(fd[1]); // Đóng đầu ghi không dùng đến

        char buf[BUFFER_SIZE];
        ssize_t n = read(fd[0], buf, sizeof(buf) - 1);
        if (n == -1) {
            perror("read");
            close(fd[0]); // dùng xong r đóng 
            _exit(1);
        }

        buf[n] = '\0'; 
        printf("Child received: %s\n", buf);

        close(fd[0]); // Đọc xong, đóng đầu đọc
        _exit(0);
    }

    // --- TIẾN TRÌNH CHA (Ghi dữ liệu) ---
    close(fd[0]); // Đóng đầu đọc không dùng đến

    const char *msg = "Hello child";
    if (write(fd[1], msg, strlen(msg)) == -1) {
        perror("write");
    }

    close(fd[1]); // Ghi xong, đóng đầu ghi

    // Chờ tiến trình con kết thúc
    waitpid(pid, NULL, 0);

    return 0;
}
