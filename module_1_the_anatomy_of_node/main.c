#include <stdlib.h>
#include <stdio.h>

typedef struct Number{
    int number;
    struct Number* next_addr;
} Number;

int main(void){
    Number n3 = {1, NULL};
    Number n2 = {2, &n3};
    Number n1 = {3, &n2};

    Number* head = &n1;

    for(int i=0; i<3; i++){
        printf("%d ", head->number);
        head = head->next_addr;
    }

    return 0;
}