#include <stdio.h>

int main(void){
    int arr[5][5] = {
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
    };

    printf("%d%d", arr[0][3], arr[1][3]);

    return 0;
}