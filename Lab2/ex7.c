#include <stdio.h>
#include <stdbool.h> // must include this lib

int main() {
    int n;
    printf("Nhap so nguyen duong n: ");
    scanf("%d", &n);

    // la so nguyen to 
    bool is_prime = true;
    if (n < 2) {
        is_prime = false;
    } else { 
        for (int i = 2; i * i <= n; i++) { // duyet tu 2, vong nhay i**2
            if (n % i == 0) {
                is_prime = false;
                break;
            }
        }
    }

    if (is_prime) {
        printf("%d la so nguyen to.\n", n);
    } else {
        printf("%d khong phai la so nguyen to.\n", n);
    }

    return 0;
}
