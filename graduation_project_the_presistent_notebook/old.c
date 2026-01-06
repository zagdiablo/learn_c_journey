#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Note
{
    char text[100];
    struct Note *next;
} note_t;

note_t *create_new_note();
int add_note(note_t **head_ref, char *text_toadd);
int load_file(note_t **head_ref);
int save_file(note_t **head_ref);


int main(void){
    note_t *head = NULL;
     // startup load
    load_file(&head);

    // test add_note
    // char text_buffer[100] = {0};
    // printf("Please enter your note: ");
    // fgets(text_buffer, sizeof(text_buffer), stdin);
    // text_buffer[strcspn(text_buffer, "\n")] = '\0';
    // add_note(&head, text_buffer);

    // check if startup load succeed
    if(head == NULL){
        printf("Fatal Error: Memory allocation failed.");
        return 1;
    }

    // add new note
    char new_note[100] = {0};
    printf("Please enter your new note: ");
    fgets(new_note, sizeof(new_note), stdin);
    new_note[strcspn(new_note, "\n") + 1] = '\0';
    add_note(&head, new_note);

    // save new note
    save_file(&head);

    // display the text
    note_t *temp = head;
    while(temp != NULL){
        printf("%s\n", temp->text);
        temp = temp->next;
    }
    
    // clean up
    while(head != NULL){
        note_t *pTemp = head->next;
        free(head);
        head = pTemp;
    }
    head = NULL;
    return 0;
}

note_t *create_new_note(){
    note_t *pTemp = malloc(sizeof(note_t));
    if(pTemp == NULL){
        printf("Fatal Error: Can't allocate memory.");
        return NULL;
    }

    pTemp->next = NULL;
    return pTemp;
}


int add_note(note_t **head_ref, char *text_toadd){
    note_t *pTemp = create_new_note();

    // assuming we confidently know the text we will add to the note is less than 100
    for(int i=0; i<strcspn(text_toadd, "\n")+1; i++){
        pTemp->text[i] = text_toadd[i];
    }
    strcat(pTemp->text, "\0");

    note_t *oldTemp = *head_ref;
    *head_ref = pTemp;
    pTemp->next = oldTemp;

    return 0;
}

int load_file(note_t **head_ref){
    FILE *pFile = fopen("note.txt", "r");
    if(pFile == NULL){
        printf("Error: Can't read text file.");
        return 1;
    }

    char text_toadd[100] = {0};
    while(fgets(&text_toadd[0], sizeof(text_toadd), pFile)){
        add_note(head_ref, text_toadd);
    }

    fclose(pFile);
    return 0;
}

int save_file(note_t **head_ref){
    FILE *pFile = fopen("note.txt", "w");
    if(pFile == NULL){
        printf("Error: Can't find text file");
        return 1;
    }

    note_t *pTemp = *head_ref;
    while(pTemp->next){
        fprintf(pFile, "%s", pTemp->text);
        pTemp = pTemp->next;
    }

    fclose(pFile);
    return 0;
}