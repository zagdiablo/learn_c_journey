#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int save(char *texto_save);
int load(char *buffer, int size);

int main(void){
    int size = 1024;
    char *text_note = malloc(size);
    load(text_note, size);
    printf("%s", text_note);

    printf("text >> ");
    fgets(text_note + strlen(text_note), size - strlen(text_note), stdin);
    text_note[strcspn(text_note, "\n")] = '\0';

    save(text_note);

    printf("What you have written so far: %s\n", text_note);

    free(text_note);
    return 0;
}

int save(char *textto_save){
    FILE *pFile = fopen("note.txt", "w");
    if(!pFile){
        printf("Can't open note.txt.");
        return 1;
    }

    fprintf(pFile, "%s", textto_save);
    
    fclose(pFile);
    pFile = NULL;
    return 0;
}

int load(char *buffer, int size){
    FILE *pFile = fopen("note.txt", "r");
    if(!pFile){
        printf("Can't open note.txt");
        return 0;
    }

    while(fgets(buffer + strlen(buffer), size - strlen(buffer), pFile)){
        if((size - strlen(buffer)) == 1){
            printf("Aw snap! its full! reallocating memory");
            size*=2;
            char *pTemp = realloc(buffer, size);
            if(!pTemp){
                printf("Fatal Error: failed to re-allocate memory!\n");
                break;
            }
            buffer = pTemp;
        }
    }

    fclose(pFile);
    pFile = NULL;
    return 0;
}