#include <stdio.h>
#include <string.h>  // use fucn strstr() to find substring :D
int main(){
    char s[256];
    printf("Nhap chuoi: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0'; // xoa ky tu xuong dong

    char sub[256];
    printf("Nhap chuoi con: "); 
    fgets(sub, sizeof(sub), stdin);
    sub[strcspn(sub, "\n")] = '\0'; // xoa ky tu xuong dong

    if (strstr(s, sub) != NULL){
        printf("Chuoi con '%s' CO trong chuoi '%s'\n", sub, s);
    } else {
        printf("Chuoi con '%s' KHONG co trong chuoi '%s'\n", sub, s);
    }
    return 0;
}