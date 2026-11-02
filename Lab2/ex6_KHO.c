#include <stdio.h>

int main() {
    int n, reversed = 0;
    printf("Nhap so nguyen duong n: ");
    scanf("%d", &n);

    int temp = n; // bien temp de ko mat n 
    while (temp > 0) {
        reversed = reversed * 10 + (temp % 10); // lay so cuoi + hang phan dvi, chuc, tram,..

        temp /= 10; // bo di chu so cuoi 
    }

    printf("So dao nguoc cua %d la: %d\n", n, reversed);

    return 0;
}
