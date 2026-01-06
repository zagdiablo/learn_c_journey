#include <stdlib.h>
#include <stdio.h>


void add_number(int* int_mem_addr, int* slots, int* slots_filled);

int main(void){
    int slots = 0;
    int slots_filled = 0;
    int is_running = 1;

    printf("Please enter how much number you want to enter: ");
    scanf("%d", &slots);

    int* pNumber = malloc(sizeof(int) * slots);
    if(pNumber == NULL){
        printf("Failed to alocate memory!");
        return 1;
    }

    for(int i = 0; i < slots; i++){
        printf("Please enter your number #%d: ", i + 1);
        scanf("%d", &pNumber[i]);
        slots_filled += 1;
    }

    // user interaction
    while(1){
        printf("Add another number? (1 = y/0 = n): ");
        scanf("%d", &is_running);
        if(!is_running){
            break;
        }else{
            add_number(pNumber, &slots, &slots_filled);
        }
    }

    // print the number
    printf("\nThese are your numbers: ");
    for(int i = 0; i < slots; i++){
        printf("%d ", pNumber[i]);
    }

    // clean up
    free(pNumber);
    pNumber = NULL;
    return 0;
}

void add_number(int* int_mem_addr, int* slots, int* slots_filled){
    int* temp = 0;
    
    if((*slots_filled) == (*slots)){
        temp = realloc(int_mem_addr, (*slots));
    }

    if(temp == NULL){
        printf("Failed to reallocate memory!");
    }else{
        printf("Please enter your number #%d", (*slots) + 1);
        scanf("%d", &temp[(*slots)]);
        (*slots) += 1;
        (*slots_filled) += 1;
        int_mem_addr = temp;
        temp = NULL;
    }
}