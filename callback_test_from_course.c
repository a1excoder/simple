#include <stdio.h>
#include <stdlib.h>

enum move_dir { MD_UP, MD_RIGHT, MD_DOWN, MD_LEFT, MD_NONE };

// Робот и его callback'и
// callback'ов может быть неограниченное количество
struct funcs {
    void (*cb)(enum move_dir);
    struct funcs* next;
};

struct robot {
    const char* name;
    struct funcs *funcs;
};

// Определите тип обработчика событий move_callback с помощью typedef
typedef void move_callback(enum move_dir dir);

// Добавить callback к роботу, чтобы он вызывался при движении
// В callback будет передаваться направление движения
void register_callback(struct robot* robot, move_callback new_cb) {
    struct funcs* new = (struct funcs*)malloc(sizeof(struct funcs));
    new->cb = new_cb;
    new->next = NULL;

    if (NULL == robot->funcs) {
        robot->funcs = new;
        return;
    }

    struct funcs* temp = robot->funcs;
    while (temp) {
        if (NULL == temp->next) {
            temp->next = new;
            return;
        }

        temp = temp->next;
    }
}

// Отменить все подписки на события.
// Это нужно чтобы освободить зарезервированные ресурсы
// например, выделенную в куче память
void unregister_all_callbacks(struct robot* robot) {
    if (NULL == robot->funcs) return;

    struct funcs* temp = robot->funcs;
    struct funcs* temp_delete = NULL;
    while (temp) {
        temp_delete = temp;
        temp = temp->next;

        free(temp_delete);
    }
}

// Вызывается когда робот движется
// Эта функция должна вызвать все обработчики событий
void move(struct robot* robot, enum move_dir dir) {
    if (NULL == robot->funcs) return;

    struct funcs* temp = robot->funcs;
    while (temp) {
        temp->cb(dir);
        temp = temp->next;
    }
}

void move_cb(enum move_dir dir) {
    switch (dir) {
        case MD_UP:
            printf("up\n");
            break;
        case MD_RIGHT:
            printf("right\n");
            break;
        case MD_DOWN:
            printf("down\n");
            break;
        case MD_LEFT:
            printf("left\n");
            break;
        case MD_NONE:
            printf("none\n");
            break;
        default:
            printf("default\n");
    }
}

void move_lol(enum move_dir dir) {
    printf("lol ) code is %d\n", dir);
}

int main(int argc, char const *argv[])
{

    struct robot r_main = {.funcs = NULL};
    register_callback(&r_main, move_cb);
    register_callback(&r_main, move_lol);

    move(&r_main, MD_UP);
    unregister_all_callbacks(&r_main);
    return 0;
}
