#!/bin/bash
#fibonanci
while true; do
    read -p "Nhap n: " n

    if ! [[ "$n" =~ ^[0-9]+$ ]]; then
        echo "Hay Nhap so nguyen duong"
        exit 1
    fi

    a=0
    b=0

    echo "Fibonaci F($n) la: "
    if [ $n == 1 ]; then 
        echo " $a "
    elif [ $n == 2 ]; then
        echo " $b "
    else 
    for ((i = 3; i < n; i ++)); do 
    fn=$((a+b))
    a=$b
    b=$fn
    echo -n "$fn "
    done
    fi
done