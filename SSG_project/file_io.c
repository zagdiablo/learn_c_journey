#include "file_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int generate_html(char *input_filename, char *output_filename){
    // variables declarations
    char title_tag[] = "{{ title }}";
    siteconfig_t site_config = {
        .title="",
        .author="",
    };

    int size = 2024;
    char *temp_buffer = malloc(size);
    
    // first of all should be loading the config
    FILE *pFileConfig = fopen("config.txt", "r");
    if(!pFileConfig){
        printf("Error: Can't read config file or file not found");
        return 3;
    }

    // temp_buffer currently holding config str per line
    while(fgets(temp_buffer, size, pFileConfig)){
        char *pTitle = strstr(temp_buffer, "title=");
        if(pTitle){
            char *title = strtok(temp_buffer, "=");
            title = strtok(NULL, "=");
            title[strcspn(title, "\n")] = '\0';
            strcpy(site_config.title, title);
        }

        char *pAuthor = strstr(temp_buffer, "author=");
        if(pAuthor){
            char *author = strtok(temp_buffer, "=");
            author = strtok(NULL, "=");
            author[strcspn(author, "\n")] = '\0';
        }
    }

    // read input file
    FILE *pFileIn = fopen(input_filename, "r");
    if(!pFileIn){
        printf("Error: Can't read file, or file not found: %s\n", input_filename);
        return 1;
    }

    // generate index html process
    FILE *pFileOut = fopen(output_filename, "w");
    if(!pFileOut){
        printf("Error: Can't write to a file or file not found: %s\n", output_filename);
        return 2;
    }

    // add top
    fprintf(pFileOut, "<html><body>\n");
    while(fgets(temp_buffer, size, pFileIn)){
        // search and replace title tag with blog title
        char *title = strstr(temp_buffer, title_tag);
        if(title){
            int pLen_before_str = title - temp_buffer;
            char *str_after_str = title + (sizeof(title_tag)-1);
            // str before {{}}
            fprintf(pFileOut, "%.*s", pLen_before_str, temp_buffer);
            // str
            fprintf(pFileOut, "%s", site_config.title);
            // str after {{}}
            fprintf(pFileOut, "%s", str_after_str);

        // if str title not detected, write as is
        }else{
            fprintf(pFileOut, "%s", temp_buffer);
        }
    }

    // add bottom
    fprintf(pFileOut, "%s", "</html></body>\n");

    fclose(pFileIn);
    fclose(pFileOut);
    fclose(pFileConfig);
    free(temp_buffer);
    pFileConfig = NULL;
    pFileIn = NULL;
    pFileOut = NULL;
    return 0;
}