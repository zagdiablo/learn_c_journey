#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[50];
    char number[50];
}Contact;

void add_contact(Contact* contact_list);
int write_contact(Contact* contact_list, int* contact_size);
int read_contact();

int main(void){
    Contact contact_lists[3] = {0};
    int contact_size = sizeof(contact_lists)/sizeof(Contact);

    for(int i=0; i<contact_size; i++){
        add_contact(&contact_lists[i]);
    }

    int file_open_satus = write_contact(&contact_lists[0], &contact_size);
    if(file_open_satus != 0){
        return 1;
    }

    read_contact();

    return 0;
}

void add_contact(Contact* contact_list){
    char name[50] = {0};
    char number[50] = {0};

    printf("Please enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strlen(name)-1] = '\0';

    printf("Please enter your phone number: ");
    fgets(number, sizeof(number), stdin);
    number[strlen(number)-1] = '\0';

    strcpy(contact_list->name, name);
    strcpy(contact_list->number, number);
}

int write_contact(Contact* contact_list, int* contact_size){
    FILE *pFile = fopen("contacts.txt", "w");
    if(pFile == NULL){
        printf("Error opening file.");
        return 1;
    }

    char str_towrite[100] = {0};
    for(int i=0; i<(*contact_size); i++){
        strcat(str_towrite, contact_list[i].name);
        strcat(str_towrite, "\n");
        strcat(str_towrite, contact_list[i].number);
        strcat(str_towrite, "\n");
        fprintf(pFile, "%s", str_towrite);
        strcpy(str_towrite, "");
    }

    fclose(pFile);
    printf("File written successfuly!\n");
    return 0;
}

int read_contact(){
    char buffer[1024] = {0};

    FILE *pFile = fopen("contacts.txt", "r");
    if(pFile == NULL){
        printf("Error opening file.");
        return 1;
    }

    while(fgets(buffer, sizeof(buffer), pFile) != NULL){
        printf("%s", buffer);
    }

    fclose(pFile);
    return 0;
}
