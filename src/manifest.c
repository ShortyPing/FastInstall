/*
Copyright (c) 2015 - 2022 Michael Steinmötzger

All rights are reserved for this project, unless otherwise
stated in a license file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "manifest.h"
#include "./utils/color.h"
#include "./utils/log_util.h"
#include "const.h"
#include "install.h"

#define INSTR_KEY 0
#define INSTR_VAL 1

#define SYNTAX_ERR(...) ERR("Syntax error on parsing manifest file \""); \
                        printf(__VA_ARGS__);                                  \
                        printf("\" at %d:%d\n", line, line_pos)





typedef unsigned t_instr;

manifest_param **parameters;
unsigned param_idx = 0;
unsigned param_max = 1;

struct build_settings_struct build_settings;

int MANIFEST_param_exists(char* name) {
    int found = 0;

    for(unsigned i = 0; i < param_idx; i++) {
        if(!strcmp(name, parameters[i]->key)) found = 1;
    }

    return found;
}

manifest_param *MANIFEST_get_param(char* name) {
    for(unsigned i = 0; i < param_idx; i++) {
        if(!strcmp(name, parameters[i]->key)) return parameters[i];
    }
    return NULL;
}

void MANIFEST_check_req_param(char* name) {
    if(!MANIFEST_param_exists(name)) {
        ERR_LN("Required parameter %s missing. Please define in manifest file!", name);
        exit(1);
    }
}

void MANIFEST_init() {
    parameters = malloc(sizeof(manifest_param *) * param_max);

    // set default settings
    build_settings.BUILD_DIR = "./";

}

void MANIFEST_add_param(char *key, char *value) {
    if (param_idx == param_max) {
        param_max++;
        parameters = realloc(parameters, sizeof(manifest_param *) * param_max);
    }

    manifest_param *param = malloc(sizeof(manifest_param));
    param->key = strdup(key);
    param->value = strdup(value);

    parameters[param_idx++] = param;
}

void MANIFEST_cfg() {

    // check for required parameters
    MANIFEST_check_req_param("FI_VERSION");
    build_settings.FI_VERSION = atoi(MANIFEST_get_param("FI_VERSION")->value);

    MANIFEST_check_req_param("INSTALL_TYPE");
    build_settings.INSTALL_TYPE = MANIFEST_get_param("INSTALL_TYPE")->value;

    MANIFEST_check_req_param("BUILD_CMD");
    build_settings.BUILD_CMD = MANIFEST_get_param("BUILD_CMD")->value;


    if(!strcmp(MANIFEST_get_param("INSTALL_TYPE")->value, "DIR")) {
        MANIFEST_check_req_param("INSTALL_DIR");
        build_settings.INSTALL_DIR = MANIFEST_get_param("INSTALL_DIR")->value;
    }

    // validate parameter values
    if(build_settings.FI_VERSION != VERSION_HASH) {
        WARN_LN("Version mismatch (Current Version: %d, File Version: %d)", VERSION_HASH, build_settings.FI_VERSION);
    }



}


void MANIFEST_parse(char *file) {
    MANIFEST_init(); // initializes param buffer
    FILE *f_ptr = fopen(file, "r");
    char buff;

    char buff_str[65535] = {};

    manifest_param *buff_param = malloc(sizeof(manifest_param));


    unsigned
            line = 1,
            line_pos = 1,
            instr_pos = 0;

    t_instr instr = INSTR_KEY;

    if (f_ptr == NULL) {
        ERR_LN("Cannot open file \"%s\". File not found or insufficient permissions.", file);
        exit(1);
    }


    while ((buff = fgetc(f_ptr)) != EOF) {


        if (buff == '\n' || buff == '\r') {
            line_pos = 0;
            line++;
            continue;
        }

        if (buff == ';') {
            if (instr == INSTR_KEY) {
                SYNTAX_ERR("instruction must have definition");
                exit(1);
            }
            buff_str[instr_pos++] = '\0';
            buff_param->value = strdup(buff_str);
            instr = INSTR_KEY;
            memset(&buff_str[0], 0, sizeof(buff_str));
            instr_pos = 0;

            MANIFEST_add_param(buff_param->key, buff_param->value);
            continue;
        }

        if (buff == '=') {
            if (instr == INSTR_VAL) {
                SYNTAX_ERR("cannot have multiple definitions in one instruction");
            }
            buff_str[instr_pos++] = '\0';
            buff_param->key = strdup(buff_str);
            instr_pos = 0;
            instr = INSTR_VAL;
            continue;
        }

        buff_str[instr_pos++] = buff;


    }

    free(buff_param->key);
    free(buff_param->value);
    free(buff_param);


    LOG_LN("Loading manifest with options: ");

    for (unsigned i = 0; i < param_idx; i++) {
        LOG_LN("-> %s : %s", parameters[i]->key, parameters[i]->value);
    }

    MANIFEST_cfg();

    fclose(f_ptr);

}