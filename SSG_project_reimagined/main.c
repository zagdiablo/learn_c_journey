#include <stdlib.h>
#include <stdio.h>
#include "file_io.h"


int main(void){
    // config object
    siteconfig_t site_config = {
        .title = "",
        .author = "",
    };

    printf("Generating site...\n");

    // load config
    int config_stat = load_config("config.txt", &site_config);
    if(config_stat){
        printf("Something went wrong, config error: %d\n", config_stat);
        return config_stat;
    }

    // generate html
    int html_status = generate_site("index.txt", "index.html", &site_config);
    if(html_status){
        printf("Something went wrong, html generating error: %d\n", html_status);
        return html_status;
    }

    printf("Site has been generated succesfuly\n");
    return 0;
}