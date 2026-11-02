// tinh luy thua
#include <stdio.h>
int pw(int a, int n){
    if (n == 0) return 1;
    else return a * pw(a, n-1);
}
int main (){
    int a, n; 
    printf("Nhap a,n: ");
    scanf("%d%d", &a, &n);

    if(n < 0) printf("Vui long nhap n duong\n");    
    else if(n == 0) printf("a^n = 1\n");
    else printf("a^n = %d\n", pw(a,n));
    
    return 0;
}
