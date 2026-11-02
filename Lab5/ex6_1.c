/* ex6.c - Liệt kê file thường trong thư mục có chứa pattern.
 * Cách dùng: ./ex6 <pattern> <thư_mục> */

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF 1024

/* Trả về 1 nếu ./ex5 in ra ít nhất 1 byte (file có chứa pattern) */
int file_contains(const char *pattern, const char *filepath) {
    int fd[2];
    if (pipe(fd) < 0) return 0;

    pid_t pid = fork();
    if (pid < 0) {
        close(fd[0]);
        close(fd[1]);
        return 0;
    }

    if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execl("./ex5", "ex5", pattern, filepath, (char *)NULL);
        _exit(127);   /* chỉ tới đây nếu execl lỗi */
    }

    close(fd[1]);
    char buf[BUF];
    ssize_t n, total = 0;
    while ((n = read(fd[0], buf, sizeof(buf))) > 0)
        total += n;

    close(fd[0]);
    waitpid(pid, NULL, 0);
    return total > 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pattern> <directory>\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    const char *dirpath = argv[2];

    DIR *dir = opendir(dirpath);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Files in \"%s\" containing \"%s\":\n", dirpath, pattern);
    printf("------------------------------------------\n");

    struct dirent *entry;
    char filepath[BUF];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(filepath, sizeof(filepath), "%s/%s", dirpath, entry->d_name);

        struct stat st;
        if (stat(filepath, &st) < 0 || !S_ISREG(st.st_mode))
            continue;

        if (file_contains(pattern, filepath))
            printf("  %s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
