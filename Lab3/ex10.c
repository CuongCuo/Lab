// In đảo ngược số nguyên bằng đệ quy
#include <stdio.h>
//
void reverse_print(int n) {
    if (n == 0) return;
    printf("%d", n % 10); // last digits
    reverse_print(n / 10); // the -2 digits
}

int main() {
    int n;
    printf("Nhap so nguyen duong n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Vui long nhap so nguyen duong!\n");
        return 1;
    }
    
    printf("So sau khi dao nguoc: ");
    reverse_print(n);
    printf("\n");
    
    return 0;   
}
