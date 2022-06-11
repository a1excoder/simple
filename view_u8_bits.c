#include <stdio.h>
#include <inttypes.h>

union u8_view_bits {
    uint8_t value;
    struct {
        uint8_t i0 : 1;
        uint8_t i1 : 1;
        uint8_t i2 : 1;
        uint8_t i3 : 1;
        uint8_t i4 : 1;
        uint8_t i5 : 1;
        uint8_t i6 : 1;
        uint8_t i7 : 1;
    } u8;
};

void view_uint8_bits(uint8_t value) {
    union u8_view_bits data = {.value = value};
    printf("%"PRIu8" is: %"PRIu8" %"PRIu8" %"PRIu8" %"PRIu8" %"PRIu8" %"PRIu8" %"PRIu8" %"PRIu8"\n", value,
           data.u8.i7, data.u8.i6, data.u8.i5, data.u8.i4, data.u8.i3, data.u8.i2, data.u8.i1, data.u8.i0);
}

int main(void) {
    view_uint8_bits(123);
    return 0;
}

// out: 123 is: 0 1 1 1 1 0 1 1
