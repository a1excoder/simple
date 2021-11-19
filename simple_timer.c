#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc < 2) {
		puts("Enter the timer number after the bin file name");
		return 1;
	}
	int num = atoi(argv[1]);

	for (int i = num; i >= 1; i--) {
		printf("%d ", i);
		sleep(1);
	}

	printf("\n%d second timer expired\n", num);
	return 0;
}
