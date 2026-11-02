#include <stdio.h>
// Viết hàm hoán đổi 2 số dùng con trỏ
void swap(int *a, int *b){
    int temp = *a;  // đảo qua biến tạm a và b
    *a = *b;
    *b = temp;
}
int main(){
    int a, b;
    printf("Nhap vao so a: ");
    scanf("%d", &a); // Nhận vào địa chỉ của a 
    printf("Nhap vao so b: ");
    scanf("%d", &b);
    swap(&a, &b); // truyền địa chỉ của a và b vào hàm swap
    printf("a = %d, b = %d\n", a, b);
    return 0;
}
