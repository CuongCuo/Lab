#include <stdio.h>
#include <stdlib.h>
int find_max(int arr[], int size){
    int max = arr[0];
    for( int i = 0; i < size; i ++){
        if ( max < arr[i]) max = arr[i];
    }
    return max;
}
int main(){
    // cấp phát động 1 mảng có n phần tử
    int n; 
    printf("Nhap so phan tu cua mang n: ");
    scanf("%d", &n);
    int *arr = (int*) malloc(n * sizeof(int));
    if (arr == NULL){
        printf("Khong the cap phat bo nho");
        return -1;
    }
    // nhập vào mảng
    printf("Nhap vao so phan tu cua mang\n ");
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    int max_val = find_max(arr, n);
    printf("Phan tu lon nhat la: %d", max_val);
    free(arr); // giải phóng mảng động
    return 0;
}
