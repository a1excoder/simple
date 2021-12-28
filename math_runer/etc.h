char *strcpy_s(char *destptr, const size_t size, const char *srcptr) {

	for (size_t i = 0; i < size; i++) {
		if (i == size-1) {
			destptr[i] = '\0';
			break;
		}

		destptr[i] = srcptr[i];
	}

	return destptr;
}

_Bool is_digit(const char c) {
	return ((c >= '0') && (c <= '9')) ? 1 : 0;
}

_Bool is_operator(const char c) {
	return ((c == '+') || (c == '-') || (c == '*') || (c == '/' || (c == '^'))) ? 1 : 0;
}

int8_t get_privilege_operation(const char c) {
	if (c == '+' || c == '-') return 1;
	else if (c == '/' || c == '*') return 2;
	else if (c == '^') return 3;
	else return 0;
}

int char_to_int(const char c) {
	int result = 0;

	if (c == '\0' || !is_digit(c)) return result;
	result = c - '0';

	return result;
}

int make_operation(const char operation, const int first, const int last) {
	if (operation == '+') return first + last;
	else if (operation == '-') return first - last;
	else if (operation == '/') return first / last;
	else if (operation == '*') return first * last;
	else if (operation == '^') {
		int result = 0;
		for (int i = 1; i <= last; i++) {
			result *= first;
		}

		return result;
	}
	else return 0;
}