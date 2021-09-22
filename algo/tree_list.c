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
