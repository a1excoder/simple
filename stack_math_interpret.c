#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>


enum opcode { BC_PUSH, BC_IPRINT, BC_IREAD, BC_IADD, BC_STOP };

struct stack_list {
    int64_t data;
    struct stack_list* next;
};

struct bc_noarg {
    enum opcode opcode;
};

struct bc_arg64 {
    enum opcode opcode;
    int64_t arg;
};

union instruction {
    enum opcode opcode;
    struct bc_arg64 as_arg64;
    struct bc_noarg as_noarg;
};

struct vm_state {
    const union instruction* commands;
    size_t commands_number;
    struct stack_list* stack;
};

struct result_data {
    int64_t data;
    bool status;
};

bool push(struct stack_list** list, int64_t data) {
    bool status = false;
    struct stack_list* new_node = (struct stack_list*)malloc(sizeof(struct stack_list));

    if (NULL != new_node) {
        status = true;
        new_node->data = data;
        new_node->next = *list;

        *list = new_node;
    }

    return status;
}

struct result_data pop(struct stack_list** list) {
    struct result_data data = {.status = false};
    struct stack_list* temp_delete = NULL;

    if (NULL != *list) {
        data.status = true;
        data.data = (*list)->data;

        temp_delete = *list;
        *list = (*list)->next;

        free(temp_delete);
    }

    return data;
}


void stack_destroy(struct vm_state* vs) {
    struct result_data res = {.status = true};

    while (res.status) {
        res = pop(&vs->stack);
        if (res.status) printf("destroy | pop(%" PRId64 ")", res.data);
    }
}

void interpret(struct vm_state data) {
    int64_t temp_i64 = 0, temp_i64_2 = 0;
    struct result_data temp_res;

    for (size_t i = 0; i < data.commands_number; i++) {
        switch (data.commands[i].opcode) {
        case BC_PUSH:
            push(&data.stack, data.commands[i].as_arg64.arg);
            break;
        case BC_IPRINT:
            temp_res = pop(&data.stack);
            if (temp_res.status) {
                printf("%" PRId64 "\n", temp_res.data);
                push(&data.stack, temp_res.data);
            }
            break;
        case BC_IREAD:
            scanf_s("%" SCNd64, &temp_i64);
            push(&data.stack, temp_i64);
            break;
        case BC_IADD:
            temp_res = pop(&data.stack);
            if (temp_res.status) {
                temp_i64 = temp_res.data;
            } else break;
            temp_res = pop(&data.stack);
            if (temp_res.status) {
                temp_i64_2 = temp_res.data;
            } else break;

            push(&data.stack, temp_i64 + temp_i64_2);
            break;
        case BC_STOP:
            i = data.commands_number;
            break;
        default:
            break;
        }
    }
    stack_destroy(&data);
}


int main(int argc, char const *argv[])
{
    const union instruction ins[] = {
        {.as_arg64 = {.opcode = BC_PUSH, .arg = 13}},
        {BC_IREAD},
        {BC_IADD},
        {.as_arg64 = {.opcode = BC_PUSH, .arg = 8}},
        {BC_IADD},
        {BC_IPRINT},
        {BC_STOP},
    };

    struct vm_state data_main = {.commands = ins, .commands_number = sizeof(ins) / sizeof(*ins)};
    interpret(data_main);
    return 0;
}
