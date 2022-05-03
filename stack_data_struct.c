#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct stack_list {
	int data;
	struct stack_list* next;
};

bool push(struct stack_list** list, int data) {
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

int pop(struct stack_list** list, bool* status) {
	int data = 0;
	struct stack_list* temp_delete = *list;

	if (NULL != *list) {
		*status = true;
		data = (*list)->data;

		temp_delete = *list;
		*list = (*list)->next;

		free(temp_delete);
	}

	return data;
}

int main(int argc, char const *argv[])
{
	struct stack_list* main_node = NULL;
	push(&main_node, 777);
	push(&main_node, 123);

	bool status = false;

	int int_data = pop(&main_node, &status);
	if (status) printf("pop(%d)\n", int_data);

	status = false;
	int_data = pop(&main_node, &status);
	if (status) printf("pop(%d)\n", int_data);

	status = false;
	int_data = pop(&main_node, &status);
	if (status) printf("pop(%d)\n", int_data);

	return 0;
}