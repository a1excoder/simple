#include <stdio.h>
#include <stdlib.h>

typedef struct nNode {
	int data;
	struct nNode *next;
} tNode;

typedef tNode *nNodePtr;

void create(nNodePtr *head, nNodePtr *tail, int value);
void rem(nNodePtr *head, nNodePtr *tail);
void view_all_nodes(nNodePtr head);



int main(void)
{
	nNodePtr head = NULL, tail = NULL;

	create(&head, &tail, 34);
	create(&head, &tail, 33214);

	rem(&head, &tail);

	create(&head, &tail, 9234);

	view_all_nodes(head);

	return 0;
}

void create(nNodePtr *head, nNodePtr *tail, int value)
{
	nNodePtr new_node = (nNodePtr)malloc(sizeof(tNode));

	if (new_node != NULL) {
		new_node->data = value;
		new_node->next = NULL;

		if (*head == NULL) {
			*head = new_node;
		} else {
			(*tail)->next = new_node;
		}
		*tail = new_node;
	} else {
		puts("[ERROR] - no free memory.");
	}
}

void rem(nNodePtr *head, nNodePtr *tail)
{
	if (*head == NULL) {
		puts("[ERROR] - list is empty");
	} else {
		nNodePtr tempPtr = *head;
		*head = (*head)->next;

		if (*head == NULL)
			*tail = NULL;

		free(tempPtr);
	}
}

void view_all_nodes(nNodePtr head)
{
	if (head != NULL) {
		while (head != NULL) {
			printf("%d->", head->data);
			head = head->next;
		}
		printf("NULL");
	}
}
