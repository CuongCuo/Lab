// Ngay trong nam 
#include <stdio.h>
#include <stdbool.h>
bool leap_year(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

bool ngay_ok(int d, int m, int y) {
    if (m < 1 || m > 12 || d < 1 || d > 31) {
        return false;
    } // phép so sánh d <= trả về true or false
    if (m == 2) { // thang 2 co  28 or 29 ngay 
        return d <= (leap_year(y) ? 29 : 28); // bt điều kiện ? true : false
    }
    if (m == 4 || m == 6 || m == 9 || m == 11) {
        return d <= 30;
    }
    return true;
}
int main() {
    int d,m,y;
    printf("Nhap ngay, thang, nam: ");
    scanf("%d%d%d", &d,&m,&y);
    if (ngay_ok(d,m,y)){
        printf("Ngay hop le\n");
    } else{
        printf("Ngay khong hop le\n");
    }
    return 0;
}
