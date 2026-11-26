#!/bin/bash

# 1.1 Chuyển đến thư mục home và liệt kê toàn bộ nội dung
cd ~ || exit 1
ls -la

# 1.2 Đếm tổng số file .c trong thư mục home
count=$(find ~ -maxdepth 1 -type f -name "*.c" | wc -l)
echo "So file .c trong thu muc home: $count"

# 1.3 Nhập N, tính tổng 1..N và lưu vào Result_ex1.txt
read -p "Nhap so nguyen N: " N
sum=0
for ((i = 1; i <= N; i++)); do
    sum=$((sum + i))
done

echo "Tong tu 1 den $N la: $sum" > Result_ex1.txt
echo "Da luu ket qua vao Result_ex1.txt"
