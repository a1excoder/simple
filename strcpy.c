#include <stdio.h>

char *strcpy(char *destptr, const char *srcptr);

int main(void) {

	const char str1[] = "Hello, World!";
	char str2[8];
	strcpy(str2, str1);
	puts(str2);

	return 0;
}

char *strcpy(char *destptr, const char *srcptr) {

	char c;
	while ((c = *(srcptr++)) != '\0') {
		*(destptr++) = c;
	}
	*(destptr++) = '\0';

	return destptr;
}
