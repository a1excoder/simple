#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

static int8_t BINARY_VALUES[] = { 1, 2, 4, 8, 16, 32, 64, 128 };

void from_int8_to_binary_string(const int8_t number, char* remote_buffer) {
	float data = (float)number;
	char buffer[] = "00000000";

	if (number < 0) {
		data *= -1;
		buffer[0] = '1';

		// if number < 0 :/

	}
	else {
		for (uint8_t i = 8; i >= 1; i--) {
			if (data != (float)number && data > 0 && floor(data) != data) {
				buffer[i] = '1';
				data = (int8_t)data;
			}
			data /= 2;
		}
	}


	strcpy_s(remote_buffer, 9, buffer);
}

int8_t from_binary_string_to_int8(const char* binary_data) {

	int8_t data = 0;
	for (uint8_t i = 7, j = 0; i >= 1; i--, j++) {
		if (binary_data[i] == '1' && j <= 7) {
			data += BINARY_VALUES[j];
		}
	}
	return data;
}

int main(void)
{
	char buff[9];
	from_int8_to_binary_string(117, buff);
	printf("from int8_t to binary => %s\n", buff);

	int8_t int8_data_from_binary = from_binary_string_to_int8(buff);
	printf("from binary(int8_t) to int8_t => %d\n", int8_data_from_binary);

	return 0;
}
