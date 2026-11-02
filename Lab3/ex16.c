#include <stdio.h>
#include <stdlib.h>
int main(){
    int n; 
    printf("Nhap so luong sv: ");
    scanf("%d",&n);

    float *arr = (float*) malloc(n * sizeof(float));
    printf("Nhap so diem cua tung sinh vien\n");
    if(arr == NULL) printf("Cap phat that bai!");

    for(int i = 0; i < n; i++){
        scanf("%f",&arr[i]); // gan vao dia chi
    }
    float avg = 0;
    float tong = 0;
    for(int i = 0; i < n; i++){
        tong += arr[i];
    }
    avg = tong/n;
    printf("Trung binh ca lop co so diem la: %.2f", avg);
    free(arr);
    return 0;
}
