#include<stdio.h>
/*Yêu cầu: Viết chương trình nhập một số nguyên n trong khoảng từ 0 đến 255, sau đó in ra
biểu diễn nhị phân của số đó dưới dạng 8 bit.
Ví dụ:
 Input: 77
 Output: 01001101 */
int main (){
    int n; 
    printf("Nhap n: ");
    scanf("%d",&n);
    // in ra dang 8 bit;
    for (int i= 7; i >= 0; i--){
        printf("%d",(n >> i) & 1);
    }
    return 0;
}