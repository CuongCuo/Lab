#include <stdio.h>
// May tinh tien dien
int tinh_tien_dien(int so_dien){
    if (so_dien <= 50){
        return so_dien * 1800;
    } else if (so_dien <= 100){
        return 50 * 1800 + (so_dien - 50) * 2300;
    } else{
        return 50 * 1800 + 50 * 2300 + (so_dien - 100) * 2800;
    }
}

int main() {
    printf("Nhap so dien tieu thu: ");
    int so_dien;
    scanf("%d", &so_dien);
    int tien_dien = tinh_tien_dien(so_dien);
    printf("So tien su dung: %d VND\n", tien_dien);
    // phan mo rong VAT 10%
    int tien_VAT = (tien_dien) * 10 /100;
    printf("Tien VAT la:  %d VND\n", tien_VAT);
    return 0;
}

