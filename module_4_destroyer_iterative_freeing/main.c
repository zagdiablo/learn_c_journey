#include <stdio.h>
#include <stdlib.h>


typedef struct Number{
    int number;
    struct Number *next_node;
} number_t;


number_t *create_node(int value);
void front_push(number_t **ppNumber, int value);

int main(void){
    number_t *head_ref = NULL;
    
    front_push(&head_ref, 1);
    front_push(&head_ref, 3);
    front_push(&head_ref, 2);
    front_push(&head_ref, 5);
    front_push(&head_ref, 4);

    number_t *temp = head_ref;
    while(1){
        printf("This is the value of the node: #%p: %d\n", temp, temp->number);
        if(temp->next_node == NULL){
            break;
        }else{
            temp = temp->next_node;
        }
    }

    // clean up
    while(head_ref != NULL){
        number_t *next_to_clean = head_ref->next_node;
        printf("Cleaning up #%p\n", head_ref);
        free(head_ref);
        printf("Success..., continue.\n");
        head_ref = next_to_clean;
    }

    printf("Done.\n");
    return 0;
}

number_t *create_node(int value){
    number_t *pTemp = malloc(sizeof(number_t));
    pTemp->number = value;
    pTemp->next_node = NULL;

    return pTemp;
}

void front_push(number_t **ppNumber, int value){
    number_t *temp = create_node(value);
    temp->next_node = *ppNumber;
    *ppNumber = temp;
}