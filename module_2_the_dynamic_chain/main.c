#include <stdlib.h>
#include <stdio.h>

typedef struct Number{
    int number;
    struct Number* next_addr;
} Number;

Number* create_node(int value);

int main(void){
    Number* head = create_node(1);
    Number* middle = create_node(2);
    Number* tail = create_node(3);

    head->next_addr = middle;
    middle->next_addr = tail;

    Number* next_node = head;
    while(next_node != NULL){
        printf("%d ", next_node->number);
        next_node = next_node->next_addr;
    }

    free(head);
    free(middle);
    free(tail);

    return 0;
}

Number* create_node(int value){
    Number* pNumber = malloc(sizeof(Number));
    pNumber->number = value;
    pNumber->next_addr = NULL;

    return pNumber;
}