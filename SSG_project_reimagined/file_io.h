#ifndef FILE_IO_H
#define FILE_IO_H

typedef struct SiteConfig{
    char title[100];
    char author[100];
}siteconfig_t;

int load_config(char *file_name, siteconfig_t *site_config);
int generate_site(char *input_file, char *output_name, siteconfig_t *site_config);

#endif