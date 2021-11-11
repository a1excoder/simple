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

enum TYPES get_file_name(const char *full_name) {
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

	int j = 0;
	for (int i = size_to_dot; i < strsize; i++) {
		str_type[j] = *((full_name - strsize-1) + i);
		j++;
	}

	return check_type_by_str(str_type);
}

int main(void)
{
	char fname[] = "test.bla";
	if (get_file_name(fname) == TXT) {
		printf("file type is txt\n");
	}

	if (get_file_name(fname) == PNG) {
		printf("file type is png\n");
	}

	if (get_file_name(fname) == JPG) {
		printf("file type is jpg\n");
	}

	if (get_file_name(fname) == MP4) {
		printf("file type is mp4\n");
	}

	if (get_file_name(fname) == ANOTHER) {
		printf("file type is another\n");
	}

	return 0;
}