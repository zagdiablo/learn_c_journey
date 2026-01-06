#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Note{
    char text[100];
    struct Note *next;
} note_t;

note_t *create_note();
int add_note(note_t **ppNote, char *text);
int save_notes(note_t **ppNote);
int load_notes(note_t **ppNote);

int main(void){
    note_t *head = NULL;
    
    load_notes(&head);

    char new_note[100] = {0};
    printf("Please enter your note: ");
    fgets(new_note, sizeof(new_note), stdin);
    new_note[strcspn(new_note, "\n")+1] = '\0';
    add_note(&head, new_note);

    
    note_t *pTemp = head;
    while(pTemp != NULL){
        printf("%s", pTemp->text);
        pTemp = pTemp->next;
    }
    
    save_notes(&head);

    // clean up
    while(head){
        note_t *next_to_clean = head->next;
        free(head);
        head = next_to_clean;
    }

    return 0;
}

note_t *create_note(){
    note_t *pTemp = malloc(sizeof(note_t));
    if(!pTemp){
        printf("Failed to allocate memory.");
        return NULL;
    }
    pTemp->next = NULL;

    return pTemp;
}

int load_notes(note_t **ppNote){
    FILE *pFile = fopen("note.txt", "r");
    if(!pFile){
        printf("Error: Can't read file.");
        return 1;
    }

    char toadd_text[100] = {0};
    while(fgets(toadd_text, sizeof(toadd_text), pFile)){
        if(strchr(toadd_text, '\n')){
            add_note(ppNote, toadd_text);
            continue;
        }
    }

    fclose(pFile);
    pFile = NULL;
    return 0;
}

int add_note(note_t **ppNote, char *text){
    note_t *pTemp = create_note();
    if(!pTemp){
        printf("Failed to create note in memory.");
        return 1;
    }
    strcpy(pTemp->text, text);

    pTemp->next = *ppNote;
    *ppNote = pTemp;

    return 0;
}

int save_notes(note_t **ppNote){
    FILE *pFile = fopen("note.txt", "w");
    if(!pFile){
        printf("Error: Can't read file.");
        return 1;
    }

    note_t *next_note = *ppNote;
    while(next_note){
        fprintf(pFile, "%s", next_note->text);
        next_note = next_note->next;
    }

    fclose(pFile);
    pFile = NULL;
    return 0;
}