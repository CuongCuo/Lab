// sum of digits
#include <stdio.h>
int sum_digits(int n){
    if (n == 0) return 0;
    else return n % 10 + sum_digits(n / 10);
}
int main(){
    int n;
    printf("Nhap so nguyen duong n: ");
    scanf("%d", &n);
    printf("Tong cac chu so cua %d la: %d\n", n, sum_digits(n));
    return 0;   
}
