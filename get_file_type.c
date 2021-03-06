#include <stdio.h>
#include <string.h>

enum TYPES {
	JPG, PNG, TXT, MP4, ANOTHER // ...
};

static enum TYPES check_type_by_str(const char *type) {
	if (!strcmp("txt", type)) {
		return TXT;
	}
	if (!strcmp("jpg", type)) {
		return JPG;
	}
	if (!strcmp("png", type)) {
		return PNG;
	}
	if (!strcmp("mp4", type)) {
		return MP4;
	}
	return ANOTHER;
}

enum TYPES get_file_type(const char *full_name) {
	int size_to_dot, strsize = 0;
	char c, cc;
	while ((c = *(full_name++)) != '\0') {
		if (cc != '.') {
			if (c == '.') {
				cc = '.';
			}
			size_to_dot++;
		}
		strsize++;
	}
	char str_type[strsize - size_to_dot];

	for (int i = size_to_dot, j = 0; i < strsize; i++, j++) {
		str_type[j] = *((full_name - strsize) + i-1); // str_type[j] = *((full_name - strsize-1) + i);
	}

	return check_type_by_str(str_type);
}

int main(void)
{
	char fname[] = "test.mp4";
	if (get_file_type(fname) == TXT) {
		printf("file type is txt\n");
	}

	if (get_file_type(fname) == PNG) {
		printf("file type is png\n");
	}

	if (get_file_type(fname) == JPG) {
		printf("file type is jpg\n");
	}

	if (get_file_type(fname) == MP4) {
		printf("file type is mp4\n");
	}

	if (get_file_type(fname) == ANOTHER) {
		printf("file type is another\n");
	}

	return 0;
}
