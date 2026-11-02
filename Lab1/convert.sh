#!/bin/bash 
#Decimal -> Hex using bc
while true; do 
	read -p "enter a decimal number" dec
	# read from stdin
	if [ -n "$dec" ]; then
		# using bc to convert dec to hex
		hex=$(echo "obase=16; $dec" | bc)
		echo "Hex num is: $hex"
	fi
done
