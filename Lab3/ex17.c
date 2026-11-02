#include<stdio.h>
#include<stdlib.h>
int main(){
    int n; 
    printf("Nhap so khoan chi: ");
    scanf("%d", &n);
    
    int *arr = (int*) malloc(n * sizeof(int));
    if(arr == NULL) printf("Cap phat that bai!");
    for(int i = 0; i < n; i++) scanf("%d",&arr[i]);
    int Tong = 0;
    for(int i =0; i<n; i++) Tong += arr[i];
    int max = arr[0];
    for(int i =0; i<n; i++){
        if(max < arr[i]) max = arr[i];
    }
    printf("Tong chi tieu trong ngay la: %d\n", Tong);
    printf("Khoan chi lon nhat la: %d\n", max);
    printf("Danh sach khoan chi:\n");
    for(int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }
    free(arr);
    return 0;
}

