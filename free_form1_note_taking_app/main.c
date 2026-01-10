#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Line{
    char line[100];
    struct Line *next;
} line_t;

int read_file(char *buffer, char *filename);

int main(void){
    char buffer[100] = {0};
    read_file(buffer, "note.txt");

    // printf("The content of the file is: %s\n", buffer);

    return 0;
}

int read_file(char *buffer, char *filename){
    FILE *pFile = fopen(filename, "r");
    if(!pFile){
        printf("Failed opening file %s\n", filename);
        return 1;
    }

    while(fgets(buffer, 100, pFile)){
        char *str_found = strstr(buffer, "zag");
        if(str_found){
            int lenbefore = str_found - buffer;
            char *lenafter = str_found + 3;
            printf("%.*s", lenbefore, buffer);
            printf("%s", "This is an inserted string");
            printf("%s", lenafter);
        }
    }

    fclose(pFile);
    pFile = NULL;
    return 0;
}