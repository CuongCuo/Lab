#include <stdio.h>
void inSoDu(long long balance) {
    printf("--> So du hien tai: %lld VNĐ\n", balance);
}
long long nhapSoTien(const char *thongBao) {
    long long amount;
    printf("%s", thongBao);
    scanf("%lld", &amount);
    return amount;
}
void deposit(long long *balance, long long amount) {
    if (amount <= 0) {
        printf("[Loi] So tien nap phai lon hon 0!\n");
    } else {
        *balance += amount;
        printf(">> Nap thanh cong: +%lld VNĐ\n", amount);
        inSoDu(*balance);
    }
}
void withdraw(long long *balance, long long amount) {
    if (amount <= 0) {
        printf("[Loi] So tien rut phai lon hon 0!\n");
    } else if (amount > *balance) {
        printf("[Loi] Giao dich khong hop le! So du khong du.\n");
        inSoDu(*balance);
    } else {
        *balance -= amount;
        printf(">> Rut thanh cong: -%lld VNĐ\n", amount);
        inSoDu(*balance);
    }
}
int main() {
    long long balance = 500000; // Số dư ban đầu
    int chon = -1;

    while (chon != 0) {
        printf("\n================ ATM MENU ================\n");
        inSoDu(balance);
        printf("1. Nap tien\n");
        printf("2. Rut tien\n");
        printf("0. Thoat\n");
        printf("Chon thao tac (0-2): ");
        scanf("%d", &chon);
        if (chon == 1) {
            long long amount = nhapSoTien("Nhap so tien muon nap: ");
            deposit(&balance, amount);
        } 
        else if (chon == 2) {
            long long amount = nhapSoTien("Nhap so tien muon rut: ");
            withdraw(&balance, amount);
        } 
        else if (chon == 0) {
            printf("Cam on ban da su dung dich vu!\n");
        } 
        else {
            printf("[Loi] Lua chon khong hop le, vui long chon lai.\n");
        }
    }
    return 0;
}