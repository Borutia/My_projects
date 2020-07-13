#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Lnode {
    ElemType data;
    struct Lnode *next;
} LNode;

LNode *create_LinkList(void) {
    int data;
    LNode *head, *p, *q;
    head = p = (LNode *) malloc(sizeof (LNode));
    head->next = NULL;
    do {
        scanf("%d", & data);
        q = (LNode *) malloc(sizeof (LNode));
        q->data = data;
        q->next = p->next;
        p->next = q;
        p = q;
    } while (getchar() != '\n');
    return (head);
}

void printList(LNode* list) {
    while (1) {
        printf(" ");
        list = list->next;
        if (list->next == NULL) {
            printf("%d\n", list->data);
            break;
        } else
            printf("%d", list->data);
    }
}

int min_int_linked_list(LNode *L) {
    int min;
    LNode *p1 = L;
    min = p1->next->data;
    while(p1->next != NULL) {
        p1 = p1->next;
        if(p1->data < min)
            min = p1->data;
    }
    return min;
}

int max_int_linked_list(LNode *L) {
    int max ;
    LNode *p1 = L;
    max = p1->next->data;
    while(p1->next != NULL) {
        p1 = p1->next;
        if(max < p1->data)
            max = p1->data;
    }
    return max;
}

void swap_int_linkedlist(LNode *L) {
    LNode *a = L;
    int min = min_int_linked_list(a);
    int max = max_int_linked_list(a);
    if(min == max) return;

    LNode *p1;
    LNode *c1 = L;
    while(c1 && c1->data != min) {
        p1 = c1;
        c1 = c1->next;
    }

    LNode *p2;
    LNode *c2 = L;
    while(c2 && c2->data != max) {
        p2 = c2;
        c2 = c2->next;
    }

    if(p1 != NULL) p1->next = c2;
    else L = c2;
    if(p2 != NULL) p2->next = c1;
    else L = c1;

    LNode *swap = c2->next;
    c2->next = c1->next;
    c1->next = swap;
}

int main() {

    LNode *a;
    a = create_LinkList();
    printf("Linked List A = ");
    printList(a);

    swap_int_linkedlist(a);
    printf("swap min max = ");
    printList(a);

    return 0;
}