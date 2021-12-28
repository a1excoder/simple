#include <stdio.h>

#include "./stack_values.h"
#include "./stack_operations.h"
#include "./etc.h"

int get_simple_result(const char *str) {
	int pos = 0, result = 0;
	int data_from_stack[2];
	char top;
	stack_node_value *stack_values = NULL;
	stack_node_operation *stack_operation = NULL;

	while (str[pos] != '\0') {
		view_stack_values(stack_values);
		puts("");
		view_stack_operations(stack_operation);
		puts("\n");
		if (is_digit(str[pos])) push_value(&stack_values, char_to_int(str[pos]));
		else if (is_operator(str[pos])) {
			top = top_operation(&stack_operation);
			if (top == '0' || get_privilege_operation(top) < get_privilege_operation(str[pos]))
				push_operation(&stack_operation, str[pos]);

			else if (get_privilege_operation(top) > get_privilege_operation(str[pos])) {
					data_from_stack[0] = pop_value(&stack_values);
					data_from_stack[1] = pop_value(&stack_values);
					push_value(&stack_values, 
						make_operation(
							pop_operation(
								&stack_operation), data_from_stack[1], data_from_stack[0]));
					continue;
			} else if (top == '(')
				push_operation(&stack_operation, str[pos]);

		} else if (str[pos] == '(') {
			push_operation(&stack_operation, str[pos]);
		} else if (str[pos] == ')') {

			if (top_operation(&stack_operation) != '(') {
				data_from_stack[0] = pop_value(&stack_values);
				data_from_stack[1] = pop_value(&stack_values);
				push_value(&stack_values, 
					make_operation(
						pop_operation(
							&stack_operation), data_from_stack[1], data_from_stack[0]));

				if (top_operation(&stack_operation) == '(') {
					pop_operation(&stack_operation);
				} else continue;

			} else {
				pop_operation(&stack_operation);
			}
		}

		if (str[pos+1] == '\0') {
			result = pop_value(&stack_values);
			break;
		}

		pos++;
	}

	return result;
}

int main(void)
{
	char *string = "1 + ((7 - 2) * 4)";
	int res = get_simple_result(string);
	printf("%d\n", res);
	return 0;
}
