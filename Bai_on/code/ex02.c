#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 2.1 Mở Data.txt để đọc và Data_copy.txt để ghi
    FILE *fin = fopen("Data.txt", "r");
    if (!fin) { perror("fopen Data.txt"); return 1; }

    FILE *fout = fopen("Data_copy.txt", "w");
    if (!fout) { perror("fopen Data_copy.txt"); fclose(fin); return 1; }

    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        fputc(ch, fout);
    }
    fclose(fin);
    fclose(fout);

    // 2.2 Nối thêm chuỗi vào cuối Data_copy.txt
    fout = fopen("Data_copy.txt", "a");
    if (!fout) { perror("fopen append"); return 1; }
    fprintf(fout, "\nGoodbye, see you again.\n");
    fclose(fout);

    // Đếm và hiển thị số ký tự, số dòng của Data_copy.txt
    fin = fopen("Data_copy.txt", "r");
    if (!fin) { perror("fopen read"); return 1; }

    long chars = 0, lines = 0;
    int prev = '\n';
    while ((ch = fgetc(fin)) != EOF) {
        chars++;
        if (ch == '\n') lines++;
        prev = ch;
    }
    if (chars > 0 && prev != '\n') lines++; // Dòng cuối không có '\n'
    fclose(fin);

    printf("So ky tu: %ld\nSo dong: %ld\n", chars, lines);
    return 0;
}
