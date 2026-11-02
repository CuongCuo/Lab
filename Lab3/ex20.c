#include <stdio.h>
#include <stdlib.h>
int main() {
    int n;
    printf("Nhap so luong nguoi tham gia: ");
    scanf("%d", &n);
    if (n <= 0) return -1;
    // 2. Cấp phát động mảng lưu điểm đánh giá
    int *arr = (int*) malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Loi cap phat bo nho!\n");
        return 1;
    }
// tao mang count 1 - count 5
    int count[6] = {0}; 
    int sum = 0;

    printf("NHAP DIEM DANH GIA (1 - 5)");
    for (int i = 0; i < n; i++) {
        do {
            printf("Nguoi thu %d (1-5): ", i + 1);
            scanf("%d", &arr[i]);
            if (arr[i] < 1 || arr[i] > 5) {
                printf("Diem khong hop le! Vui long nhap lai tu 1 den 5.\n");
            }
        } while (arr[i] < 1 || arr[i] > 5);
        count[arr[i]]++;
        sum += arr[i];
    }
    float avg = (float)sum / n; // ep kieu so float 
    int max_freq = count[1]; // gan bang 1 
    int mode = 1;
    for (int i = 2; i <= 5; i++) {
        if (count[i] > max_freq) {
            max_freq = count[i];
            mode = i;
        }
    }
    printf("\n=== KET QUA KHAO SAT ===\n");
    printf("Thong ke tan suat cac muc diem:\n");
    for (int i = 1; i <= 5; i++) {
        printf("- Muc %d diem: %d lan\n", i, count[i]);
    }
    printf("-------------------------------\n");
    printf("Diem trung binh: %.2f\n", avg);
    printf("Muc diem xuat hien nhieu nhat: %d (%d lan)\n", mode, max_freq);
    free(arr);

    return 0;
}