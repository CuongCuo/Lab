#!/bin/bash
# chuyen so thap phan sang hex
# dung lenh bc

while true; do
    read -p "Nhap so thap phan: " dec
    if [ -n "$dec" ]; then 
        hex=$(echo 'obase=16; ibase=10; '$dec' ' | bc)
        echo "So thap luc $dec la $hex"
    else 
        echo "Thoat chuong trinh"
        break
    fi
done