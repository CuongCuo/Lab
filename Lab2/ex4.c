#include <stdio.h>

int main() {
    int score;
    printf("Nhap diem (0 - 100): ");
    scanf("%d", &score);

    if (score < 0 || score > 100) {
        printf("Diem khong hop le!\n");
    } else if (score >= 90) {
        printf("Xep loai: A\n");
    } else if (score >= 80) {
        printf("Xep loai: B\n");
    } else if (score >= 70) {
        printf("Xep loai: C\n");
    } else if (score >= 60) {
        printf("Xep loai: D\n");
    } else {
        printf("Xep loai: F\n");
    }

    return 0;
}
