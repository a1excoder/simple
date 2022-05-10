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
        if (res.status) printf("destroy | pop(%" PRId64 ")\n", res.data);
    }
}

typedef void (*stack_func_type) (struct vm_state*, size_t);

void interpret_push(struct vm_state* state, size_t command_index) {
    push(&state->stack, state->commands[command_index].as_arg64.arg);
}

void interpret_iprint(struct vm_state* state, size_t command_x) {
    struct result_data temp_res = pop(&state->stack);
    if (temp_res.status) {
        printf("%" PRId64 "\n", temp_res.data);
        push(&state->stack, temp_res.data);
    }
}

void interpret_iread(struct vm_state* state, size_t command_x) {
    int64_t temp_i64;
    scanf_s("%" SCNd64, &temp_i64);
    push(&state->stack, temp_i64);
}

void interpret_iadd(struct vm_state* state, size_t command_x) {
    int64_t temp_i64 = 0, temp_i64_2 = 0;

    struct result_data temp_res = pop(&state->stack);
    if (temp_res.status) temp_i64 = temp_res.data;
    else return;

    temp_res = pop(&state->stack);
    if (temp_res.status) temp_i64_2 = temp_res.data;
    else return;

    push(&state->stack, temp_i64 + temp_i64_2);
}

stack_func_type my_funcs[] = {
    [BC_PUSH] = interpret_push,
    [BC_IPRINT] = interpret_iprint,
    [BC_IREAD] = interpret_iread,
    [BC_IADD] = interpret_iadd
};

void interpret(struct vm_state data) {
    int64_t temp_i64 = 0, temp_i64_2 = 0;
    struct result_data temp_res;

    for (size_t i = 0; i < data.commands_number; i++) {
        switch (data.commands[i].opcode) {
        case BC_PUSH:
            my_funcs[BC_PUSH](&data, i);
            break;
        case BC_IPRINT:
            my_funcs[BC_IPRINT](&data, 0);
            break;
        case BC_IREAD:
            my_funcs[BC_IREAD](&data, 0);
            break;
        case BC_IADD:
            my_funcs[BC_IADD](&data, 0);
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
