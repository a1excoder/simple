## My realisation dynamic linked list in C

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct nNode {
    int data;
    struct nNode *next;
} tNode;

typedef struct {
    tNode *node;
} tNodePtr;

void read_nodes(tNodePtr *node);
void delete_nodes(tNodePtr *node);
void create(tNodePtr *node, int value);
void delete_node(tNodePtr *nodeP, int value);
void edit_value(tNodePtr *nodeP, int old_value, int new_value);


int main(void)
{

    tNodePtr current = {NULL};

    create(&current, 123);
    create(&current, 52);
    create(&current, 345);
    create(&current, 778);
    create(&current, 12523);

    delete_node(&current, 778);

    read_nodes(&current);


    edit_value(&current, 52, 777);

    puts("\n");
    read_nodes(&current);

    puts("\n\n");
    delete_nodes(&current);

    return 0;
}


void read_nodes(tNodePtr *nodeP)
{
    tNode *node = nodeP->node;

    if (node != NULL) {
        while (node != NULL) {
            printf("%d->", node->data);
            node = node->next;
        }
    }
    else {
        puts("node list is empty");
    }
}

void delete_nodes(tNodePtr *nodeP)
{
    tNode *tmp = nodeP->node;

    if (nodeP->node != NULL) {
        while (tmp != NULL) {
            tNode *p = tmp;

            tmp = tmp->next;
            printf("%d is free\n", p->data);
            free(p);
        }
        nodeP->node = NULL;
    } else {
        puts("node list is empty");
    }
}

void delete_node(tNodePtr *nodeP, int value)
{
    tNode *node = nodeP->node;
    tNode *n_node;

    if (node == NULL) {
        puts("node list is empty");
    } else {
        while (node != NULL) {
            if (node->data == value) {
                n_node->next = node->next;

                free(node);
                break;
            }

            n_node = node;
            node = node->next;
        }
    }
}

void edit_value(tNodePtr *nodeP, int old_value, int new_value)
{
    tNode *node = nodeP->node;

    if (nodeP->node != NULL) {
        while (node != NULL) {
            if (node->data == old_value) {
                node->data = new_value;
                break;
            }

            node = node->next;
        }
    } else {
        puts("node list is empty");
    }
}

void create(tNodePtr *nodeP, int value)
{
    tNode *p = nodeP->node;
    tNode *pp = NULL;

    if (nodeP->node != NULL) {
        while (p != NULL) {
            pp = p;
            p = p->next;
        }
        pp->next = (tNode*)malloc(sizeof(tNode));
        pp->next->data = value;
        pp->next->next = NULL;
    } else {
        nodeP->node = (tNode*)malloc(sizeof(tNode));
        nodeP->node->data = value;
        nodeP->node->next = NULL;
    }

}
```

<br>

## My realisation dynamic stack list in C
```c
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
```

<br>

## My realisation dynamic queue list in C
```c
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
```

<br>

## Realisation from book of Paul J. Deitel and add own function for free all tree: tree list with generate random numbers for tree stack in C
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct treeNote {
    struct treeNote *leftNodePtr;
    int data;
    struct treeNote *rightNodePtr;
} typeTreeNote;

typedef typeTreeNote *typeTreeNotePtr;

void insertNode(typeTreeNotePtr *node, int value);
void inOrder(typeTreeNotePtr node);
void preOrder(typeTreeNotePtr node);
void postOrder(typeTreeNotePtr node);
void freeOrder(typeTreeNote **node);


int main() {
    typeTreeNotePtr root = NULL;

    srand(time(NULL));

    int8_t temp;
    for (int8_t i = 0; i < 10; i++) {
        temp = rand() % 100;
        printf(" %d", temp);
        insertNode(&root, temp);
    }
    puts("\n");

    inOrder(root);

    puts("\n");

    freeOrder(&root);

    return 0;
}

void insertNode(typeTreeNotePtr *node, int value)
{
    if (*node != NULL) {
        if (value > (*node)->data) {
            insertNode(&(*node)->rightNodePtr, value);
        } else if (value < (*node)->data) {
            insertNode(&(*node)->leftNodePtr, value);
        } else {
            printf("(attended)");
        }
    } else {
        *node = (typeTreeNotePtr)malloc(sizeof(typeTreeNote));
        if (*node != NULL) {
            (*node)->data = value;

            (*node)->leftNodePtr = NULL;
            (*node)->rightNodePtr = NULL;
        }

    }
}

void inOrder(typeTreeNotePtr node)
{
    if (node != NULL) {
        inOrder(node->leftNodePtr);
        printf("%d->", node->data);
        inOrder(node->rightNodePtr);
    }
}

void preOrder(typeTreeNotePtr node)
{
    if (node != NULL) {
        printf("%d->", node->data);
        inOrder(node->leftNodePtr);
        inOrder(node->rightNodePtr);
    }
}

void postOrder(typeTreeNotePtr node)
{
    if (node != NULL) {
        inOrder(node->leftNodePtr);
        inOrder(node->rightNodePtr);
        printf("%d->", node->data);
    }
}

void freeOrder(typeTreeNote **node)
{
    if (*node != NULL) {
        freeOrder(&(*node)->leftNodePtr);
        freeOrder(&(*node)->rightNodePtr);
        printf("%d is free\n", (*node)->data);
        free(*node);
    }
}
```
