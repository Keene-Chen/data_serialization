/* Example: parse a simple configuration file */

#include "ini.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int version;
    const char* name;
    const char* email;
    int active;
    float pi;
} configuration;

static int handler(void* user, const char* section, const char* name, const char* value)
{
    configuration* pconfig = (configuration*)user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("protocol", "version")) {
        pconfig->version = atoi(value);
    }
    else if (MATCH("user", "name")) {
        pconfig->name = strdup(value);
    }
    else if (MATCH("user", "email")) {
        pconfig->email = strdup(value);
    }
    else if (MATCH("user", "active")) {
        pconfig->active = atoi(value);
    }
    else if (MATCH("user", "pi")) {
        pconfig->pi = atof(value);
    }
    else {
        return 0; /* unknown section/name, error */
    }
    return 1;
}

int main(int argc, char* argv[])
{
    configuration config;
    config.version = 0; /* set defaults */
    config.name    = NULL;
    config.email   = NULL;
    config.active  = 0;
    config.pi      = 0;

    if (ini_parse("./res/test.ini", handler, &config) < 0) {
        printf("Can't load 'test.ini'\n");
        return 1;
    }
    printf("Config loaded from 'test.ini': \n");
    printf("version = %d\n", config.version);
    printf("name    = %s\n", config.name);
    printf("email   = %s\n", config.email);
    printf("active  = %d\n", config.active);
    printf("pi      = %f\n", config.pi);

    if (config.name)
        free((void*)config.name);
    if (config.email)
        free((void*)config.email);

    return 0;
}