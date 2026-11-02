#include <stdio.h>
int main(){
	int n; 
	printf("Nhap so nguyen n (0-255) : ");
	if(scanf("%d", &n) != 1 || n < 0 || n > 255) {
		printf("Loi nhap lieu");
		return 0;}

	printf("Bieu Dien nhi phan 8 bit");
	for (int i =7; i >= 0; i--){
		printf("%d", (n>>i) & 1);} // shift 1 -> AND1 to have MSB bit
	printf("\n");
	return 0;
}
 
