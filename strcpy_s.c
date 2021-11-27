#include <stdio.h>

char *strcpy_s(char *destptr, const size_t buff_size, const char *srcptr);

int main(void) {

	const char str1[] = "Hello Alex.";

	char str2[12];
	const size_t str2_size = sizeof(str2) / sizeof(*str2);

	strcpy_s(str2, str2_size, str1);
	puts(str2);

	return 0;
}

char *strcpy_s(char *destptr, const size_t buff_size, const char *srcptr) {

	for (size_t i = 0; i < buff_size; i++) {
		if (i == buff_size-1) {
			destptr[i] = '\0';
			break;
		}
		destptr[i] = srcptr[i];
	}

	return destptr;
}
