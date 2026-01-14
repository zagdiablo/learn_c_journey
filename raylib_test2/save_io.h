#ifndef SAVE_IO
#define  SAVE_IO

typedef struct SaveFile{
    char username[100];
    int high_score;
}savefile_t;


savefile_t load_savefile(char *save_location);
int write_savefile(char *save_location, int high_score);


#endif