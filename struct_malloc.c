#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

typedef struct {
	char data_name[16];
	
	struct {
		char fname[32];
		uint8_t age;
	} users[2];
} data;

int main(int argc, const char **argv)
{
	int *arr_ten = (int*)malloc(11 * sizeof(int));
	// int arr_ten[11];
	
	for (int i = 0; i <= 10; i++) {
		*(arr_ten+i) = i*i*i*i;
	}
	
	putchar('[');
	for (int i = 0; i <= 10; i++) {
		printf("%d", *(arr_ten+i));
		if (i != 10) printf(", ");
	}
	putchar(']');
	
	free(arr_ten);
	
	srand(time(NULL));
	data *ndata = (data*)calloc(3, sizeof(data));
	printf("\ndata size is: %ld bytes\n", sizeof(data));
	
	for (uint8_t i = 0; i < 3; i++) {
		strcpy((ndata+i)->data_name, "test name hz");
		for (uint8_t j = 0; j < 2; j++) {
			strcpy((ndata+i)->users[j].fname, "MB Alex Rudenko.");
			(ndata+i)->users[j].age = rand() % 256;
		}
	}
	
	for (int i = 0; i < 3; i++) {
		puts((ndata+i)->data_name);
		for (uint8_t j = 0; j < 2; j++) {
			printf("%s(%d)\n", (ndata+i)->users[j].fname, (ndata+i)->users[j].age);
		}
		putchar('\n');
	}
	
	free(ndata);
	return 0;
}

