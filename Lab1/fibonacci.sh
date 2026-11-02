#!/bin/bash
# read from stdin
read -p "Nhap n: " n

if ! [[ "$n" =~ ^[0-9]+$ ]]; then
    echo "Hay Nhap so nguyen duong"
    exit 1
fi

a=0
b=1

echo "Fibonacci tu F0 to F($n):"

for (( i=0; i<=n; i++ ))
do
    if [ $i -eq 0 ]; then
        echo -n "$a "
    elif [ $i -eq 1 ]; then
        echo -n "$b "
    else
        fn=$((a + b))
        a=$b
        b=$fn
        echo -n "$fn "
    fi
done
echo ""
