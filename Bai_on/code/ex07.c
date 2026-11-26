#include <stdio.h>
#include <sys/stat.h>

int main(void) {
    char filename[256];
    printf("Nhap ten file: ");
    scanf("%255s", filename);

    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("stat");
        return 1;
    }

    printf("Kich thuoc: %lld bytes\n", (long long)st.st_size);
    printf("Quyen truy cap: ");
    printf("%c", S_ISDIR(st.st_mode) ? 'd' : '-');
    printf("%c%c%c", (st.st_mode & S_IRUSR) ? 'r' : '-',
                     (st.st_mode & S_IWUSR) ? 'w' : '-',
                     (st.st_mode & S_IXUSR) ? 'x' : '-');
    printf("%c%c%c", (st.st_mode & S_IRGRP) ? 'r' : '-',
                     (st.st_mode & S_IWGRP) ? 'w' : '-',
                     (st.st_mode & S_IXGRP) ? 'x' : '-');
    printf("%c%c%c\n", (st.st_mode & S_IROTH) ? 'r' : '-',
                       (st.st_mode & S_IWOTH) ? 'w' : '-',
                       (st.st_mode & S_IXOTH) ? 'x' : '-');
    return 0;
}
