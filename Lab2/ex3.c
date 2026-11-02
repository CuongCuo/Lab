#include <stdio.h>
int main() {
	int x,k;
	
	printf("Nhap so nguyen: ");
	scanf("%d", &x);

	printf("Nhap vi tri can check: ");
	scanf("%d", &k);

	// extract bit k using shift + and bit (>> , &1)
	if(k <= 32 && k >= 0) {int bit = (x >> k) & 1;
	printf(" Bit %d cua %d la: %d\n",k,x,bit);}
	return 0;}

