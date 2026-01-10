#include <stdio.h>
#include "file_io.h"

int main(void){
    printf("Generating index.html...\n");
    int result = generate_html("index.txt", "index.html");
    if(result){
        printf("Something went wrong, error code: %d\n", result);
        return result;
    }

    printf("Done! check index.html\n");

    return 0;
}