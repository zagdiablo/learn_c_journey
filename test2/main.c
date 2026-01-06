#include <stdio.h>
#include <stdlib.h>

float get_average(int a, int b, int c);

int main(void){
    float result = get_average(3, 3, 5);
    printf("%f", result);

    return 0;
}

float get_average(int a, int b, int c){
    float sum = a + b + c;
    return sum / 3;
}