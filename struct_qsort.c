#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

// Мы хотим, чтобы в структуре user хранились ссылки только на строчки из кучи.
typedef struct { char* addr; } string_heap ;

/*  Тип для идентификаторов пользователей
    и его спецификаторы ввода и вывода для printf */
typedef uint64_t uid;
#define PRI_uid PRIu64
#define SCN_uid SCNu64

enum city {C_SARATOV, C_MOSCOW, C_PARIS, C_LOS_ANGELES, C_OTHER};

/*  Массив, где элементам перечисления сопоставляются их текстовые представления */
const char* city_string[] = {
  [C_SARATOV] = "Saratov",
  [C_MOSCOW] = "Moscow",
  [C_PARIS] = "Paris",
  [C_LOS_ANGELES] = "Los Angeles",
  [C_OTHER] = "Other"
};


struct user {
  const uid id;
  const string_heap name;
  enum city city;
};

typedef int comparator_type(const struct user*, const struct user*);
typedef int comparator_type_true(const void*, const void*);

int comparator_uid(const struct user* a, const struct user* b) {
    if (a->id > b->id) return 1;
    if (a->id < b->id) return -1;
    return 0;
}

int comparator_c_names(const struct user* a, const struct user* b) {
    return strcmp(city_string[a->city], city_string[b->city]);
}

int comparator_heap_names(const struct user* a, const struct user* b) {
    return strcmp(a->name.addr, b->name.addr);
}

/* Сортировать массив пользователей по полю uid по возрастанию */
void users_sort_uid(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), (comparator_type_true*)comparator_uid);
}

/* Сортировать массив пользователей по полю name */
/* Порядок строк лексикографический; можно использовать компаратор
   строк -- стандартную функцию strcmp */
void users_sort_name(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), (int(*)(const void*, const void*))comparator_heap_names);
}

/* Сортировать массив по _текстовому представлению_ города */
void users_sort_city(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), (int(*)(const void*, const void*))comparator_c_names);
}

int main()
{
    struct user users[] = {{.id = 33}, {.id = 13}, {.id = 84}, {.id = 56}};

    for (size_t i = 0; i < 4; i++) {
        printf("%zu) .id = %" PRIu64 "\n", i, users[i].id);
    }
    puts("");

    users_sort_uid(users, 4);

    for (size_t i = 0; i < 4; i++) {
        printf("%zu) .id = %" PRIu64 "\n", i, users[i].id);
    }

    return 0;
}
