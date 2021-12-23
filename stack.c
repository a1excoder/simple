#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    TEXT, INT, FLOAT, CHAR
} node_type;

typedef struct vnode {
    node_type type;
    void *data;
    struct vnode *next;
} stack_node;

bool push(stack_node ** snp, void *data, node_type type);
stack_node *pop(stack_node ** snp);
void get_stack_data(stack_node *snp);
void get_all_stack_data(stack_node **snp);
void free_data_and_stack_struct(stack_node *snp);
void get_stack_data_and_free(stack_node *snp);
char *string_copy_secure(char *to_string, size_t size_buffer, const char *from_string);

int main(int argc, const char **argv) {
    stack_node *p = NULL;

    void *p1_data = malloc(sizeof("Hello"));
    string_copy_secure((char*)p1_data, sizeof("Hello"), "Hello");
    push(&p, p1_data, TEXT);

    void *p2_data = malloc(sizeof("World"));
    string_copy_secure((char*)p2_data, sizeof("World"), "World");
    push(&p, p2_data, TEXT);

    void *p3_data = malloc(sizeof(int));
    *(int*)p3_data = 777;
    push(&p, p3_data, INT);

    get_stack_data_and_free(pop(&p));
    get_stack_data_and_free(pop(&p));


    puts("");
    get_all_stack_data(&p);
    free_data_and_stack_struct(pop(&p));

    puts("");
    get_all_stack_data(&p);

    return 0;
}

bool push(stack_node ** snp, void *data, const node_type type) {
    void *new_stack = malloc(sizeof(stack_node));
    stack_node *stp = *snp;
    if (new_stack == NULL) return false;

    ((stack_node*)new_stack)->type = type;
    ((stack_node*)new_stack)->data = data;
    ((stack_node*)new_stack)->next = NULL;

    if (*snp == NULL) *snp = new_stack;
    else {
        while (stp != NULL) {
            if (stp->next == NULL) {
                stp->next = new_stack;
                break;
            }

            stp = stp->next;
        }
    }

    return true;
}

stack_node *pop(stack_node ** snp) {
    stack_node *stp = *snp;
    stack_node *previous = NULL;
    previous = stp;
    if (stp == NULL) return NULL;
    if (stp->next == NULL) {
        *snp = NULL;
        return stp;
    }

    while (stp != NULL) {
        if (stp->next == NULL) {
            previous->next = NULL;
            break;
        }

        previous = stp;
        stp = stp->next;
    }

    return stp;
}

void get_stack_data(stack_node *snp) {
    if (snp == NULL) puts("stack struct is free");
    else {
        if (snp->type == TEXT) printf("stack string is |%s|\n", (char*)snp->data);
        else if (snp->type == INT) printf("stack int data is: |%d|\n", *(int*)snp->data);
        else if (snp->type == CHAR) printf("stack char is: |%c|\n", *(char*)snp->data);
        else if (snp->type == FLOAT) printf("stack char is: |%f|\n", *(float *)snp->data);
    }
}

void get_all_stack_data(stack_node **snp) {
    stack_node *stp = *snp;

    if (stp == NULL) puts("stack is free");
    else {
        while (stp != NULL) {
            get_stack_data(stp);
            stp = stp->next;
        }
    }
}

void free_data_and_stack_struct(stack_node *snp) {
    free(snp->data);
    free(snp);
    puts("trashed");
}

void get_stack_data_and_free(stack_node *snp) {
    get_stack_data(snp);
    free_data_and_stack_struct(snp);
}

char *string_copy_secure(char *to_string, size_t size_buffer, const char *from_string) {
    for (size_t i = 0; i < size_buffer; i++) {
        if (i == size_buffer - 1) {
            to_string[i] = '\0';
            break;
        }
        to_string[i] = from_string[i];
    }

    return to_string;
}
