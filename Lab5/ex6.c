/*
 * grepdir.c
 * Liệt kê tất cả các file trong thư mục có chứa từ cần lọc.
 *
 * Cách dùng: ./grepdir <pattern> <directory>
 *
 * Thuật toán:
 *   1. Mở thư mục bằng opendir() / readdir().
 *   2. Với mỗi file thường (S_ISREG), gọi ex5.exe (linuxgrep) thông qua
 *      popen() để chạy và đọc stdout của nó.
 *   3. Nếu ex5 in ra ít nhất 1 dòng → file chứa pattern → in tên file.
 *
 * Lưu ý: popen() = pipe + fork + exec gộp lại, tiện dụng trên MinGW/Windows.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>      /* opendir, readdir, closedir */
#include <sys/stat.h>    /* stat, S_ISREG              */

#define BUF 1024

/*
 * grep_file_via_ex5()
 * Gọi chương trình ex5.exe với lệnh: ex5.exe <pattern> <filepath>
 * Dùng popen() để bắt stdout của ex5.
 * Trả về 1 nếu ex5 in ra ít nhất 1 dòng (tức là file chứa pattern).
 */
int grep_file_via_ex5(const char *pattern, const char *filepath) {
    char cmd[BUF * 2];

    /* Tạo chuỗi lệnh: "ex5.exe <pattern> <filepath>" */
    snprintf(cmd, sizeof(cmd), ".\\ex5.exe \"%s\" \"%s\"", pattern, filepath);

    /* Mở pipe tới ex5, đọc stdout của nó */
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen");
        return 0;
    }

    /* Đọc thử 1 ký tự: nếu có output → file chứa pattern */
    int has_output = (fgetc(fp) != EOF);

    pclose(fp);
    return has_output;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pattern> <directory>\n", argv[0]);
        exit(1);
    }

    const char *pattern = argv[1];
    const char *dirpath = argv[2];

    /* Mở thư mục */
    DIR *dir = opendir(dirpath);
    if (dir == NULL) {
        perror("opendir");
        exit(1);
    }

    struct dirent *entry;
    char filepath[BUF];

    printf("Files in \"%s\" containing \"%s\":\n", dirpath, pattern);
    printf("------------------------------------------\n");

    /* Duyệt từng entry trong thư mục */
    while ((entry = readdir(dir)) != NULL) {

        /* Bỏ qua "." và ".." */
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        /* Ghép đường dẫn đầy đủ */
        snprintf(filepath, sizeof(filepath), "%s/%s", dirpath, entry->d_name);

        /* Chỉ xử lý file thường (không xử lý thư mục con) */
        struct stat st;
        if (stat(filepath, &st) < 0) continue;
        if (!S_ISREG(st.st_mode)) continue;

        /* Gọi ex5.exe qua popen() để kiểm tra */
        if (grep_file_via_ex5(pattern, filepath)) {
            printf("  %s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
