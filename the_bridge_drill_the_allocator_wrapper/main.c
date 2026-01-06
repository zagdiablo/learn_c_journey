#include <stdio.h>
#include <stdlib.h>

int allocate_array(int** pArray, int* array_size);

int main(void){
    int* pNumber = NULL;
    int** pNumberAddr = &pNumber;
    int size = sizeof(int) * 5;

    int success = allocate_array(pNumberAddr, &size);
    if(success){
        printf("Memory allocation failed");
        return 1;
    }

    for(int i=0; i<5; i++){
        pNumber[i] = i+1;
    }

    for(int i=0; i<5; i++){
        printf("%d ", pNumber[i]);
    }

    free(pNumber);
    pNumber = NULL;
    return 0;
}

int allocate_array(int** pArray, int* array_size){
    *pArray = malloc((*array_size));
    if(*pArray == NULL){
        return 1;
    }

    return 0;
}   