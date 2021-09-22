#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    int value;
    struct stack *stackPtr;
} typeStack;

void insert_new_stack(typeStack **pStack, int data);
void delete_stack(typeStack **pStack);
void read_stack_list(typeStack *pStack);


int main(void)
{

    typeStack *current_stack = NULL;

    insert_new_stack(&current_stack, 12);
    insert_new_stack(&current_stack, 3432);
    insert_new_stack(&current_stack, 15632);

    delete_stack(&current_stack);
    read_stack_list(current_stack);

    insert_new_stack(&current_stack, 777);
    read_stack_list(current_stack);

    delete_stack(&current_stack);
    read_stack_list(current_stack);

    return 0;
}

void insert_new_stack(typeStack **pStack, int data)
{
    typeStack *new_stack = (typeStack*)calloc(1, sizeof(typeStack));
    if (new_stack != NULL) {
        new_stack->value = data;
        new_stack->stackPtr = *pStack;

        *pStack = new_stack;
    } else
        puts("No memory for insert new stack.");
}

void delete_stack(typeStack **pStack)
{
    typeStack *temp_stack;

    if (*pStack != NULL) {
        temp_stack = *pStack;
        *pStack = (*pStack)->stackPtr;

        free(temp_stack);
    } else
        puts("stack is NULL.");
}

void read_stack_list(typeStack *pStack)
{
    if (pStack->stackPtr != NULL) {
        while (pStack != NULL) {
            printf("%d->", pStack->value);
            pStack = pStack->stackPtr;
        }
        puts("");
    } else
        puts("stack is NULL.");
}