#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int idata = 1000; // Cấp phát trong data segment

int main(void) {
    int istack = 150;    // Cấp phát trong stack segment
    // Mở O_RDONLY (hoặc O_RDWR) để tiến trình cha có thể đọc được sau khi con lseek
    int fd = open("Hello.txt", O_RDONLY);
    if (fd == -1) { perror("open Hello.txt"); return 1; }

    pid_t childPid = fork();
    if (childPid < 0) { perror("fork"); close(fd); return 1; }

    if (childPid == 0) {
        // Tiến trình con
        printf("[Con] Truoc: idata = %d, istack = %d\n", idata, istack);
        idata *= 2;
        istack *= 2;
        printf("[Con] Sau:   idata = %d, istack = %d\n", idata, istack);

        // Dịch file offset đến byte thứ 7
        lseek(fd, 7, SEEK_SET);
        close(fd);
        return 0;
    } else {
        // Tiến trình cha
        wait(NULL);
        printf("[Cha] idata = %d, istack = %d\n", idata, istack);

        char buf[256];
        ssize_t n = read(fd, buf, sizeof(buf) - 1);
        if (n >= 0) {
            buf[n] = '\0';
            printf("[Cha] Noi dung doc tu Hello.txt: %s\n", buf);
        }
        close(fd);
    }
    return 0;
}

/*
 * TRA LOI CAU HOI:
 * 1. Con in idata=2000, istack=300; Cha van in idata=1000, istack=150.
 *    Vi sau fork(), cha va con co khong gian bo nho rieng (Copy-on-Write).
 * 2. Cha doc duoc tu byte thu 7 tro di ("What is your name?").
 *    Ket luan: Sau fork(), cha va con DUNG CHUNG open file description
 *    nen dung chung vi tri con tro file (file offset).
 */
