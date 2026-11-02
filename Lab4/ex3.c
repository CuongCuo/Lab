/*
Bài 3: Hệ thống tài khoản ngân hàng
Mô tả bài toán: Một tài khoản ngân hàng có số dư và cần thực hiện các thao tác nạp và rút
tiền.
Yêu cầu:
Khai báo struct Account gồm id, balance.
Viết hàm deposit(Account *acc, int amount).
Viết hàm withdraw(Account *acc, int amount).
Cập nhật trực tiếp số dư thông qua con trỏ.
Không cho phép rút nếu số dư không đủ.
*/
#include <stdio.h>
#include<stdlib.h>
typedef struct Account{
    int id;
    float balance;
} Account;
void deposit(Account *acc, int amount){
    if(amount <= 0) return;
    else {acc -> balance += amount;} 
}
void withdraw(Account * acc, int amount){
    if(amount <= 0) return;
    else if (acc->balance < amount) printf("So du ko du!");
    else {acc -> balance -= amount;}
}
int main(){
    Account *acc = (Account*)malloc(sizeof(Account)); // chi co 1 nguoi n = 1
    float balance,amount;
    printf("nhap so du ban dau: \n");
    scanf("%f", &balance);
    
    acc->balance = balance; // gan so du ban dau vao struct
    printf("So du hien tai: %.2f\n", acc->balance);

    printf("Nhap so tien muon nap/rut\n");
    scanf("%f", &amount);
    
    int lua_chon;
    printf("1. Nap tien\n 2. Rut tien\n");
    scanf("%d", &lua_chon);
    if (lua_chon == 1) {
        deposit(acc, amount);
        printf("Nap tien thanh cong! So du moi: %.2f\n", acc->balance);
    }
    else if (lua_chon == 2) {
        withdraw(acc, amount);
        printf("So du sau khi rut: %.2f\n", acc->balance);
    }
    free(acc);
    return 0;
}
