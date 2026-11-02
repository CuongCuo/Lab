#include <stdio.h>
void cong_tru(int a, int b, int *tong, int *hieu){
    *tong = a + b;
    *hieu = a - b;
    return;
}

int main(){
    int a, b, tong, hieu;
    printf("Nhap  so a, b: ");
    scanf("%d%d", &a, &b);
    
    cong_tru(a,b,&tong,&hieu); // truyền địa chỉ của tong, hieu

    printf("Tong = %d va Hieu = %d", tong, hieu);
    return 0;
}
