#include <stdio.h>
#include <unistd.h>

int main(void) {
    // Gọi hàm fork(): trả về PID của tiến trình con cho tiến trình cha,
    // trả về 0 cho tiến trình con, và trả về -1 nếu có lỗi.
    pid_t pid = fork();

    if (pid < 0) {
        // Lỗi khi tạo tiến trình con
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Tiến trình con thực thi đoạn này
        printf("Tôi là con (PID con: %d, PID cha: %d)\n", getpid(), getppid());
    } else {
        // Tiến trình cha thực thi đoạn này
        printf("Tôi là cha, con có PID = %d (PID cha: %d)\n", pid, getpid());
    }

    return 0;
}