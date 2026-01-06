#include <stdlib.h>
#include <stdio.h>

typedef struct Number{
    int number;
    struct Number* next_addr;
} Number;

void push_front(Number** head_ref, int value);

Number* create_node(int value);

int main(void){
    Number* head = NULL;

    push_front(&head, 50);
    push_front(&head, 30);
    push_front(&head, 20);
    push_front(&head, 10);
    push_front(&head, 0);

    Number* next_node = head;
    while(next_node != NULL){
        printf("%d ", next_node->number);
        next_node = next_node->next_addr;
    }

    free(head);
    return 0;
}

Number* create_node(int value){
    Number* pNumber = malloc(sizeof(Number));
    pNumber->number = value;
    pNumber->next_addr = NULL;

    return pNumber;
}

void push_front(Number** head_ref, int value){
    if(*head_ref == NULL){
        *head_ref = create_node(value);
    }else{
        Number* pTemp = *head_ref;
        *head_ref = create_node(value);
        (*head_ref)->next_addr = pTemp;
    }
}