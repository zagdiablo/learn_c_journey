#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save_io.h"


savefile_t load_savefile(char *save_location){
    savefile_t load_save = {0};
    // int file_created = 0;

    // read save file
    FILE *pFile = fopen(save_location, "r");
    // if not found, create save file
    if(!pFile){
        pFile = fopen(save_location, "w");
        if(!pFile){
            printf("Fatal Error: save file I/O handling error, cant read save file or file not found.");
            return load_save; // NULL values
        }

        // write basic data
        fprintf(pFile, "username=%s\n", "player");
        fprintf(pFile, "highscore=%d\n", 0);
        // file_created = 1;
        fclose(pFile); // close after writing

        // reopen for reading
        FILE *pFile = fopen(save_location, "r");
        if(!pFile){
            printf("Fatal Error: save file I/O handling error, cant read save file or file not found.");
            return load_save; // NULL values
        }
    }

    int size = 1024;
    char *buffer = malloc(1024);

    // if save file exist
    while(fgets(buffer, size, pFile)){
        char *found_score = strstr(buffer, "highscore=");
        if(found_score){
            char *score = strtok(buffer, "=");
            score=strtok(NULL, "="); // get the score
            score[strcspn(score, "\n")] = '\0'; // clean 
            load_save.high_score = atoi(score); // guaranteed number, if not -> crash game
        }
    }

    free(buffer);
    fclose(pFile);
    pFile = NULL;
    return load_save;
}


int write_savefile(char *save_location, int high_score){
    // save file should be guaranteed to exist
    // it is always checked and if not exist created at InitGame by load_savefile
    FILE *pFile = fopen(save_location, "w");
    if(!pFile){
        printf("Fatal Error: save file I/O handling error, cant read save file or file not found.");
        return 1;
    }

    // write data
    fprintf(pFile, "username=player\nhighscore=%d", high_score);

    fclose(pFile);
    return 0;
}