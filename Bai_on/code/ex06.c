#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    char dest[256], src[256], buf[4096];
    int choice;

    printf("Nhap ten file muon tao: ");
    scanf("%255s", dest);
    printf("Chon (1: nhap tu ban phim, 2: chep tu file khac): ");
    scanf("%d", &choice);
    getchar(); // Xóa ký tự '\n' còn lại

    int out = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out == -1) { perror("open dest"); return 1; }

    ssize_t n;
    if (choice == 1) {
        printf("Nhap noi dung (Ctrl+D de ket thuc):\n");
        while ((n = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
            write(out, buf, n);
        }
    } else if (choice == 2) {
        printf("Nhap ten file nguon: ");
        scanf("%255s", src);
        int in = open(src, O_RDONLY);
        if (in == -1) { perror("open src"); close(out); return 1; }
        while ((n = read(in, buf, sizeof(buf))) > 0) {
            write(out, buf, n);
        }
        close(in);
    } else {
        printf("Lua chon khong hop le.\n");
    }

    close(out);
    return 0;
}
