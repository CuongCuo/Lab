/*
Viết chương trình linuxls.c mô phỏng lệnh shell ls. Chương trình nhận 1 tham số đầu vào:
đường dẫn thư mục trong argv[1].
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>      /* opendir, readdir, closedir */
#include <sys/stat.h>    /* stat, S_ISREG, S_ISDIR     */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);
    }
    const char *dirpath = argv[1];
    /* Mở thư mục */
    DIR *dir = opendir(dirpath);
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }
    struct dirent *entry;
    struct stat st;
    char filepath[1024];
    /* Duyệt từng entry trong thư mục */
    while ((entry = readdir(dir)) != NULL) {
        /* Bỏ qua "." và ".." giống ls mặc định */
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;
        /* Ghép đường dẫn để lấy thông tin file */
        snprintf(filepath, sizeof(filepath), "%s/%s", dirpath, entry->d_name);
        stat(filepath, &st);
        /* In tên: thư mục thêm '/' ở cuối cho dễ phân biệt */
        if (S_ISDIR(st.st_mode))
            printf("%s/\n", entry->d_name);
        else
            printf("%s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}
