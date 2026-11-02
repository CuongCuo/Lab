#include <stdio.h>
int gia_san_pham(int ma){
    if (ma == 1) return 10000;
    else if (ma == 2) return 12000;
    else if (ma == 3) return 15000;
    else return -1; // mã ko hợp lệ
}
// đặt Đủ tiền là 1, Thiếu là 0, ko hợp lệ là -1
int check(int ma, int tien){
    int gia = gia_san_pham(ma);
    if (gia == -1) return -1; // mã k hợp lệ
    if (tien >= gia) return 1; // đủ 
    else return 0; // thiếu
}
int main(){
    int ma, tien;
    printf("Nhap so tien da bo vao may: ");
    scanf("%d", &tien);
    printf("Nhap ma do uong (1. Nuoc suoi, 2. Tra chanh, 3. Ca phe lon): ");
    scanf("%d", &ma);
    
    int ket_qua = check(ma, tien);
    
    if (ket_qua == -1) printf("Ma san pham khong hop le!\n");
    else if (ket_qua == 0) printf("Khong du tien! So tien con thieu la: %d dong.\n", gia_san_pham(ma) - tien);
    else if (ket_qua == 1) {
        int gia = gia_san_pham(ma);
        if (ma == 1) printf("Ban da mua: Nuoc suoi.\n");
        else if (ma == 2) printf("Ban da mua: Tra chanh.\n");
        else if (ma == 3) printf("Ban da mua: Ca phe lon.\n");
        
        printf("So tien thua: %d dong.\n", tien - gia);
    }
    return 0;
}
