#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct heap_string {
  char* addr;
};

// скопировать в кучу
struct heap_string halloc( const char* s ) {
    if (s == NULL) return (struct heap_string) {.addr = NULL};

    struct heap_string h = {.addr = (char*)malloc(*s)};

    for (size_t i = 0; i < *s; i++) {
        h.addr[i] = s[i];
    }

    return h;
}

// освободить память
void heap_string_free( struct heap_string h ) {
    free(h.addr);
}


int64_t cube(int64_t x) {
    return x*x*x;
}

int64_t squre(int64_t x) {
    return x*x;
}

void math_func(int64_t x, int64_t (*do_math)(int64_t)) {
    printf("%d in this function is %d\n", x, do_math(x));
}

int64_t comparator1(const int64_t* a, const int64_t* b) {
    if (*a > *b) return 1;
    if (*a < *b) return -1;
    return 0;
}

int64_t comparator2(const int64_t* a, const int64_t* b) {
    if (*a > *b) return -1;
    if (*a < *b) return 1;
    return 0;
}

void view_array(const int64_t* array, const size_t size) {
    if (array && size > 0) {
        for (size_t i = 0; i < size; i++) {
            printf("array[%d] = %d\n", i, *(array + i));
        }
    }
}

int main(void)
{

    struct heap_string my = halloc("Hello my friend!");
    printf("data: |%s|\n", my.addr);
    heap_string_free(my);

    int64_t (*cube_fp)(int64_t) = cube;
    void (*cube_fvp)(const int64_t) = (void (*)(const int64_t)) cube_fp;
    int64_t (*cube_fpp)(int64_t) = (int64_t (*)(int64_t)) cube_fvp;

    const int64_t x = 3;
    printf("%d^3 = %d\n", x, cube_fpp(x));

    math_func(5, squre);
    math_func(5, cube_fpp);

    int64_t array[] = {55, 235, 74, 23, 6542, 27, 11, 45542, 55, 545};
    const size_t size = sizeof(array) / sizeof(array[0]);

    view_array(array, size);
    qsort(array, size, sizeof(array[0]), (int(*)(const void*, const void*))comparator1);

    puts("");
    view_array(array, size);
    qsort(array, size, sizeof(array[0]), (int(*)(const void*, const void*))comparator2);

    puts("");
    view_array(array, size);

    return 0;
}
