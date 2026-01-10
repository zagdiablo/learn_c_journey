#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file_io.h"

int load_config(char *file_name, siteconfig_t *site_config){
    // variable declarations
    int size = 2048;
    char *buffer = malloc(size);

    // create a pointer to config file
    FILE *pFileConfig = fopen(file_name, "r");
    if(!pFileConfig){
        printf("Can't load config file %s, or file not found", file_name);
        return 1;
    }

    // load config
    while(fgets(buffer, size, pFileConfig)){
        // read title
        char *pTitle = strstr(buffer, "title=");
        if(pTitle){
            char *title = strtok(buffer, "=");
            title = strtok(NULL, "=");
            title[strcspn(title, "\n")] = '\0';
            strcpy(site_config->title, title);
        }

        // read author
        char *pAuthor = strstr(buffer, "author=");
        if(pAuthor){
            char *author = strtok(buffer, "=");
            author = strtok(NULL, "=");
            author[strcspn(author, "\n")] = '\0';
            strcpy(site_config->author, author);
        }
    }

    free(buffer);
    fclose(pFileConfig);
    pFileConfig = NULL;
    buffer = NULL;
    return 0;
}

int generate_site(char *input_file, char *output_name, siteconfig_t *site_config){
    // variable declarations
    char title_tag[] = "{{ title }}";
    char author_tag[] = "{{ author }}";
    int size = 2048;
    char *buffer = malloc(size);

    // read input file
    FILE *pFileIn = fopen(input_file, "r");
    if(!pFileIn){
        printf("Can't open file %s, or file not found", input_file);
        return 1;
    }

    // set output file as write mode
    FILE *pFileOut = fopen(output_name, "w");
    if(!pFileOut){
        printf("Can't write to file %s, or file not found", output_name);
        return 2;
    }

    // generate site
    // add html opening tag
    fprintf(pFileOut, "<html><body>\n");

    while(fgets(buffer, size, pFileIn)){
        char *title_found = strstr(buffer, title_tag);
        char *author_found = strstr(buffer, author_tag);
        
        if(title_found){
            int str_len_before_title = title_found - buffer;
            char *str_len_after_title = title_found + (sizeof(title_tag)-1);

            // inject title to html
            fprintf(pFileOut, "%.*s", str_len_before_title, buffer);
            fprintf(pFileOut, "%s", site_config->title);
            fprintf(pFileOut, "%s", str_len_after_title);
        }else if(author_found){
            int str_len_before_author = author_found - buffer;
            char *str_len_after_author = author_found + (sizeof(author_tag) - 1);

            // inject author into html
            fprintf(pFileOut, "%.*s", str_len_before_author, buffer);
            fprintf(pFileOut, "%s", site_config->author);
            fprintf(pFileOut, "%s", str_len_after_author);
        }else{
            // if not title, write it as is
            fprintf(pFileOut, "%s", buffer);
        }

    }
    // add html closing tag
    fprintf(pFileOut, "</body></html>");
    
    // Clean up
    free(buffer);
    fclose(pFileIn);
    fclose(pFileOut);
    pFileIn = NULL;
    pFileOut = NULL;
    buffer = NULL;
    return 0;
}