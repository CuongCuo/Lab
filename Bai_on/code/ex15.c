#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

volatile sig_atomic_t running = 1;

void handle_sigint(int sig) {
    (void)sig;
    running = 0;
}

void list_dir(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) { perror("opendir"); return; }

    printf("=== Danh sach file trong '%s' ===\n", path);
    struct dirent *entry;
    struct stat st;
    char fullpath[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        if (stat(fullpath, &st) == 0) {
            printf("%s (%lld bytes)\n", entry->d_name, (long long)st.st_size);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *folder = (argc > 1) ? argv[1] : ".";

    struct sigaction sa = {0};
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    while (running) {
        list_dir(folder);
        sleep(60); // Tự động bị ngắt ngay khi nhận Ctrl+C
    }

    printf("\nProgram is terminated by user\n");
    return 0;
}
