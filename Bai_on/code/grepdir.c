#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

// Kiểm tra xem file có chứa từ khóa hay không
static int file_contains(const char *filepath, const char *word) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) return 0;

    char line[1024];
    int found = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, word) != NULL) {
            found = 1;
            break;
        }
    }
    fclose(fp);
    return found;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Cach dung: %s <tu_can_loc> <thu_muc>\n", argv[0]);
        return 1;
    }

    DIR *dir = opendir(argv[2]);
    if (!dir) { perror("opendir"); return 1; }

    struct dirent *entry;
    char path[1024];
    struct stat st;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", argv[2], entry->d_name);
        if (stat(path, &st) == 0 && S_ISREG(st.st_mode)) {
            if (file_contains(path, argv[1])) {
                printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
    return 0;
}
