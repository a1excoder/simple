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