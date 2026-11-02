#include <stdio.h>
#include <ctype.h>
int main() {
    char s[256];
    printf("Nhap chuoi: ");
    fgets(s, sizeof(s), stdin);

    int lowwer = 0, upper = 0, digit = 0;
    for (int i = 0; s[i] != '\0'; i++){
        if (islower(s[i])){
            lowwer++;
        } else if (isupper(s[i])){
            upper++;
        } else if (isdigit(s[i])){
            digit++;
        }
    }
    printf("So ky tu thuong: %d\n", lowwer);
    printf("So ky tu hoa: %d\n", upper);
    printf("So ky tu so: %d\n", digit);
    return 0;
}
