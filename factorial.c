#include <stdio.h>

int factorial(int n) {
	if (n < 1) {
		return 1;
	}
	return n * factorial(n-1);
}

int main(void) {
	int z = 0;

	while(1) {
		printf("Enter integer: ");
		scanf("%d", &z);
		if (z == 0) break;
		printf("factorial(%d) = %d\n", z, factorial(z));
	}
	
	return 0;
}
