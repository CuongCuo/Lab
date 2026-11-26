#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Cach dung: %s <tu_can_loc> <ten_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[2], "r");
    if (!fp) { perror("fopen"); return 1; }

    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, argv[1]) != NULL) {
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}
