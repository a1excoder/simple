// structs.h

//
//
//
#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>
#include <stdint.h>

struct date {
    uint8_t day;
    uint8_t month;
    uint16_t year;
};

struct user {
    char *name;
    struct date date;
    struct {
        bool married;
        uint8_t kids;
    } family;
};

#endif // STRUCTS_H
//
//
//




// main.c

//
//
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

#include "structs.h"

#define ARR_SIZE 16

#define MUL_FALL(a, b) a * b

#ifdef ARR_SIZE
#define MUL(a, b) (a) * (b)
#endif

size_t slen(const char * s) {
    size_t sz = 0;
    for (; s[sz] != '\0'; sz++) {}
    return sz;
}

_Bool get_dyn_i64_arr(int64_t** p, size_t sz) {
    *p = malloc(sizeof(int64_t) * sz);
    return (*p != NULL) ? 1 : 0;
}

void view_user(const struct user*);

int main(void) {
    srand(time(NULL));

    const char* str = "Hello World";
    printf("|%s| slen(%zu)\n", str, slen(str));
    printf("|%s| strlen(%zu)\n", str, strlen(str));


    int64_t* p64_ = NULL;
    if (!get_dyn_i64_arr(&p64_, 16)) exit(1);
    for (size_t i = 0; i < 16; i++)
        *(p64_ + i) = (10 + i) * 10;

    for (size_t i = 0; i < 16; i++)
        printf("%p) %" PRId64 "\n", p64_ + i, *(p64_ + i));


    free(p64_);


#ifdef MUL
    printf("%d\n", MUL(12 + 8, 8));
#elif ARR_SIZE
    printf("%d\n", 0xc);
// #error Where my MUL
#else
    printf("%d\n", MUL_FALL(12 + 8, 8));
#endif

    int64_t** arr2level = (int64_t**)calloc(ARR_SIZE, sizeof(int64_t**));
    if (arr2level == NULL) {
        fprintf(stderr, "%s\n", "memory allocation error\n");
        exit(1);
    }
    for (size_t i = 0; i < ARR_SIZE; i++) {
        *(arr2level + i) = (int64_t*)calloc(ARR_SIZE, sizeof(int64_t));
        if (*(arr2level + i) == NULL) {
            fprintf(stderr, "%s\n", "memory allocation error\n");
            exit(1);
        }
        for (size_t j = 0; j < ARR_SIZE; j++) {
            *(*(arr2level + i) + j) = rand() % 257;
        }
    }

    for (size_t i = 0; i < ARR_SIZE; i++) {
        printf("addr: %p & id: %zu\n", arr2level + i, i);
        for (size_t j = 0; j < ARR_SIZE; j++) {
            printf("\t%p) %" PRId64 "\n", (*(arr2level + i) + j), *(*(arr2level + i) + j));
        }
        free(*(arr2level + i));
        *(arr2level + i) = NULL;
    }
    free(arr2level);
    arr2level = NULL;



    struct user user1 = {.name = "Alex", .date.day = 11, .date.month = 11, .date.year = 2004, .family.kids = 0, .family.married = false};
    view_user(&user1);


    return 0;
}



void view_user(const struct user* user) {
    printf("name: %s\n\tday: %" PRId8 "\n\tmonth: %" PRId8 "\n\tyear: %" PRId16 "\n\tmarried: %s\n\tkids: %" PRId8"\n",
           user->name, user->date.day, user->date.month, user->date.year, user->family.married ? "yes" : "no", user->family.kids);
}
//
//
//
