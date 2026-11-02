// number of words in a string
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int main() {
    char s[256];
    printf("Nhap chuoi: ");
    fgets(s, sizeof(s), stdin);

    int dem = 0;
    bool in_word = false;

    for(int i = 0; s[i] != '\0'; i++){
        if (isspace(s[i])){ // ham kiem tra xem co phai la blank ko 
            in_word = false; // neu gap blank thi in_word = false
        } else if (!in_word){
            in_word = true; // neu gap ki tu khong phai blank va in_word = false thi in_word = true
            dem++;
        }
    }
    printf("So tu trong chuoi la: %d\n", dem);
    return 0;
}
