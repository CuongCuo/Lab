#include <stdio.h>
#include <stdbool.h>
// Linear search function
int linear_search(int arr[], int size, int target){
    int found -0;
    for(int i = 0; i < size; i++){
    if(arr[i] == target){
	printf("%d",i);
	found = 1; }
    }
    if (!found) {
        printf("Khong tim thay %d", target);
    }
    printf("\n"); 
}
int main(){
    int n; 
    printf("nhap so luong phan tu cua mang: ");
    scanf("%d", &n); 
    
    int arr[n];
    for (int i = 0; i<n; i++){
        
        printf("Nhap phan tu thu %d: ", i+1);
        scanf("%d", &arr[i]);
    }
    printf("Nhap gia tri can tim: ");
    int target;
    scanf("%d", &target);
    printf("Ket qua tim kiem: %d\n", linear_search(arr, n, target));
    return 0;
}
