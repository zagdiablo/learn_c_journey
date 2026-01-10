#ifndef FILE_IO_H
#define FILE_IO_H

typedef struct SiteConfig{
    char title[100];
    char author[100];
} siteconfig_t;

int generate_html(char *input_filename, char *output_filename);

#endif