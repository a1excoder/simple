#include <stdlib.h>

typedef struct st_node_op
{
	char data;
	struct st_node_op *next;
} stack_node_operation;

void push_operation(stack_node_operation **main_node, char data) {
	stack_node_operation *new_node = (stack_node_operation*)malloc(sizeof(stack_node_operation));
	new_node->data = data;
	new_node->next = NULL;

	stack_node_operation *tmp_node = *main_node;

	if (*main_node == NULL) *main_node = new_node;
	else if ((*main_node)->next == NULL) (*main_node)->next = new_node;
	else {
		while (tmp_node != NULL) {
			if (tmp_node->next == NULL) {
				tmp_node->next = new_node;
				break;
			}

			tmp_node = tmp_node->next;
		}
	}
}

char top_operation(stack_node_operation **main_node) {
	stack_node_operation *tmp_node = *main_node;

	if (tmp_node == NULL) return '0';
	else if (tmp_node->next == NULL) return tmp_node->data;

	while (tmp_node != NULL) {
		if (tmp_node->next == NULL) {
			break;
		}

		tmp_node = tmp_node->next;
	}

	return tmp_node->data;
}

char pop_operation(stack_node_operation **main_node) {
	stack_node_operation *tmp_node = *main_node;
	stack_node_operation *previos = tmp_node;
	char result = '0';

	if (tmp_node == NULL) return result;
	if (tmp_node->next = NULL) {
		*main_node = NULL;
		result = tmp_node->data;
		free(tmp_node);

		return result;
	}

	while (tmp_node != NULL) {
		if (tmp_node->next == NULL) {
			previos->next = NULL;
			result = tmp_node->data;
			free(tmp_node);
			break;
		}

		previos = tmp_node;
		tmp_node = tmp_node->next;
	}

	return result;
}

void view_stack_operations(stack_node_operation *main_node) {
	stack_node_operation *tmp_node = main_node;
	int num = 1;

	while (tmp_node != NULL) {
		printf("key(%d) | value: <%c>\n", num, tmp_node->data);
		tmp_node = tmp_node->next;
		num++;
	}
}