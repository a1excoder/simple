#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

enum opcode { BC_PUSH, BC_IPRINT, BC_IREAD, BC_IADD, BC_ISUB, BC_IMUL, BC_IDIV, BC_ICMP, BC_INEG, BC_SWAP, BC_DUP, BC_STOP };

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

typedef void (*stack_func_type) (struct vm_state*);


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

void lift_unop( struct stack_list** s, int64_t (f)(int64_t)) {
    struct result_data res = pop(s);
    if (res.status) push(s, f(res.data));
}

void lift_binop( struct stack_list** s, int64_t (f)(int64_t, int64_t)) {
    int64_t temp_i64 = 0, temp_i64_2 = 0;

    struct result_data res = pop(s);
    if (res.status) temp_i64 = res.data;
    else return;

    res = pop(s);
    if (res.status) temp_i64_2 = res.data;
    else return;

    push(s, f(temp_i64, temp_i64_2));
}

int64_t i64_add(int64_t a, int64_t b) { return a + b; }
int64_t i64_sub(int64_t a, int64_t b) { return a - b; }
int64_t i64_mul(int64_t a, int64_t b) { return a * b; }
int64_t i64_div(int64_t a, int64_t b) { return a / b; }
int64_t i64_cmp(int64_t a, int64_t b) { if (a > b) return 1; else if (a < b) return -1; return 0; }

int64_t i64_neg(int64_t a) { return -a; }

void interpret_iadd( struct vm_state* state ) {
    lift_binop(&state->stack, i64_add);
    state->commands = state->commands + 1;
}

void interpret_isub( struct vm_state* state ) {
    lift_binop(&state->stack, i64_sub);
    state->commands = state->commands + 1;
}

void interpret_imul( struct vm_state* state ) {
    lift_binop(&state->stack, i64_mul);
    state->commands = state->commands + 1;
}
void interpret_idiv( struct vm_state* state ) {
    lift_binop(&state->stack, i64_div);
    state->commands = state->commands + 1;
}
void interpret_icmp( struct vm_state* state ) {
    lift_binop(&state->stack, i64_cmp);
    state->commands = state->commands + 1;
}

void interpret_ineg( struct vm_state* state) {
    lift_unop (& state->stack, i64_neg);
    state->commands = state->commands + 1;
}

void interpret_push(struct vm_state* state) {
    push(&state->stack, state->commands->as_arg64.arg);
    state->commands = state->commands + 1;
}

void interpret_iprint(struct vm_state* state) {
    struct result_data temp_res = pop(&state->stack);
    if (temp_res.status) {
        printf("%" PRId64 "\n", temp_res.data);
        push(&state->stack, temp_res.data);
    }

    state->commands = state->commands + 1;
}

void interpret_iread(struct vm_state* state) {
    int64_t temp_i64;
    scanf_s("%" SCNd64, &temp_i64);
    push(&state->stack, temp_i64);

    state->commands = state->commands + 1;
}

void interpret_swap(struct vm_state* state) {
    int64_t temp_i64 = 0, temp_i64_2 = 0;
    struct result_data res = pop(&state->stack);
    if (res.status) temp_i64 = res.data;
    else return;

    res = pop(&state->stack);
    if (res.status) temp_i64_2 = res.data;
    else return;

    push(&state->stack, temp_i64);
    push(&state->stack, temp_i64_2);

    state->commands = state->commands + 1;
}

void interpret_dup(struct vm_state* state) {
    struct result_data res = pop(&state->stack);
    if (res.status) {
        push(&state->stack, res.data);
        push(&state->stack, res.data);
    }
}

stack_func_type my_funcs[] = {
    [BC_PUSH] = interpret_push,
    [BC_IPRINT] = interpret_iprint,
    [BC_IREAD] = interpret_iread,
    [BC_IADD] = interpret_iadd,
    [BC_ISUB] = interpret_isub,
    [BC_IMUL] = interpret_imul,
    [BC_IDIV] = interpret_idiv,
    [BC_ICMP] = interpret_icmp,
    [BC_INEG] = interpret_ineg,
    [BC_SWAP] = interpret_swap,
    [BC_DUP] = interpret_dup
};

void interpret(struct vm_state data) {
    int64_t temp_i64 = 0, temp_i64_2 = 0;
    struct result_data temp_res;

    for (;;) {
        switch (data.commands->opcode) {
        case BC_PUSH:
            my_funcs[BC_PUSH](&data);
            break;
        case BC_IPRINT:
            my_funcs[BC_IPRINT](&data);
            break;
        case BC_IREAD:
            my_funcs[BC_IREAD](&data);
            break;
        case BC_IADD:
            my_funcs[BC_IADD](&data);
            break;
        case BC_ISUB:
            my_funcs[BC_ISUB](&data);
            break;
        case BC_IMUL:
            my_funcs[BC_IMUL](&data);
            break;
        case BC_IDIV:
            my_funcs[BC_IDIV](&data);
            break;
        case BC_ICMP:
            my_funcs[BC_ICMP](&data);
            break;
        case BC_INEG:
            my_funcs[BC_INEG](&data);
            break;
        case BC_SWAP:
            my_funcs[BC_SWAP](&data);
        case BC_DUP:
            my_funcs[BC_DUP](&data);
        case BC_STOP:
            stack_destroy(&data);
            return;
        default:
            break;
        }
    }
    stack_destroy(&data);
}

int main(void)
{
    const union instruction ins[] = {
        {.as_arg64 = {.opcode = BC_PUSH, .arg = 13}},
        {BC_IREAD},
        {BC_IADD},
        {.as_arg64 = {.opcode = BC_PUSH, .arg = 8}},
        {BC_IADD},
        {BC_IPRINT},
        {.as_arg64 = {.opcode = BC_PUSH, .arg = 2}},
        {BC_IMUL},
        {BC_IPRINT},
        {BC_DUP},
        {BC_STOP}
    };

    struct vm_state data_main = {.commands = ins, .commands_number = sizeof(ins) / sizeof(*ins)};
    interpret(data_main);
    return 0;
}
