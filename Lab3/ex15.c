/* Người dùng nhập điểm của n sinh viên. Chương trình cần viết các hàm riêng
để tính tổng điểm, đếm số sinh viên đạt, tìm điểm cao nhất và tìm điểm thấp nhất.*/
#include<stdio.h>
#include<stdlib.h>
float Tong_diem(float diem[], int n ){
    float Tong = 0;
    for(int i = 0; i < n; i ++){
        Tong += diem[i];
    }
    return Tong;
}
int valid_sv(float diem[], int n){
    int dem = 0;
    for(int i = 0; i < n; i++){
        if(diem[i] >= 5) dem ++;
    }
    return dem;
}
void find_max_min(float diem[], int n,float *max, float *min){
    *max = diem[0];
    *min = diem[0];
    for(int i = 0; i < n; i++){
        if (*max < diem[i]) *max = diem[i];
        if (*min > diem[i]) *min = diem[i];
    }
}
int main(){
    int n;
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);
    float *arr = (float*) malloc(n * sizeof(float)); // cấp phát động 1 mảng float
    if (arr == NULL){
        printf("Khong the cap phat bo nho");
        return -1;
    }
    printf("Nhap vao diem cua n sinh vien\n");
    for(int i = 0; i < n; i ++){
        scanf("%f",&arr[i]); // dán vào địa chỉ
    }
    float max, min;
    find_max_min(arr, n, &max, &min);
    printf("\n--- KET QUA ---\n");
    printf("Tong diem: %.1f\n", Tong_diem(arr, n));
    printf("So sinh vien dat: %d\n", valid_sv(arr, n));
    printf("Diem cao nhat: %.1f\n", max);
    printf("Diem thap nhat: %.1f\n", min);

    free(arr);
    return 0;
}
