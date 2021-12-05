#include <stdio.h>
#include <stdlib.h>

typedef struct link_node {
	int data;
	struct link_node *next;
} tNode;

typedef struct {
	tNode *node;
} tNodePtr;

tNode *create(tNodePtr *node, const int data);
void delete(tNodePtr *node, const int value);
void view(const tNodePtr *node);
void delete_all(tNodePtr *node);

int main(void)
{
	tNodePtr main_node = {NULL};
	create(&main_node, 234);
	create(&main_node, 214);
	create(&main_node, 23534);
	create(&main_node, 5);
	create(&main_node, 261);

	view(&main_node);
	puts("");
	delete(&main_node, 214);
	puts("");
	view(&main_node);

	puts("");
	delete_all(&main_node);
	puts("");
	view(&main_node);

	create(&main_node, 777);
	create(&main_node, 911);
	puts("");
	view(&main_node);

	puts("");
	delete_all(&main_node);
	puts("");
	view(&main_node);
	return 0;
}


tNode *create(tNodePtr *node, const int data) {
	tNode *new_node = (tNode*)malloc(sizeof(tNode));
	tNode *temp_node = NULL;

	new_node->data = data;

	if (node->node == NULL) node->node = new_node; 
	else {
		temp_node = node->node;
		while (temp_node->next != NULL) temp_node = temp_node->next;
		temp_node->next = new_node;
	}

	return new_node;
}

void delete(tNodePtr *node, const int value) {
	tNode *temp_node = NULL;
	tNode *delete_node = node->node;

	if (delete_node != NULL) {
		while (delete_node != NULL) {

			if (delete_node->data == value) {
				printf("%p -> %d was deleted\n", delete_node, delete_node->data);
				temp_node->next = delete_node->next;
				free(delete_node);
				break;
			}

			temp_node = delete_node;
			delete_node = delete_node->next;
		}
	} else puts("node is empty");
}

void view(const tNodePtr *node) {
	tNode *temp_node = NULL;

	if (node->node != NULL) {
		temp_node = node->node;
		while (temp_node != NULL) {
			printf("%p -> %d\n", temp_node, temp_node->data);
			temp_node = temp_node->next;
		}
	} else puts("node is empty");
}

void delete_all(tNodePtr *node) {
	tNode *delete_node = NULL;
	tNode *temp_node = node->node;

	if (temp_node != NULL) {
		while (temp_node != NULL) {
			delete_node = temp_node;
			temp_node = delete_node->next;
			printf("%p -> %d was deleted\n", delete_node, delete_node->data);
			free(delete_node);
		}
		node->node = NULL;
	} else puts("node is empty");
}