/*
Copyright (c) 2015 - 2022 Michael Steinmötzger

All rights are reserved for this project, unless otherwise
stated in a license file.
*/

#ifndef FASTINSTALL_MANIFEST_H
#define FASTINSTALL_MANIFEST_H




typedef struct {
    char *key;
    char *value;
} manifest_param;

struct build_settings_struct {
    int FI_VERSION;
    char* BUILD_DIR;
    char* INSTALL_TYPE;
    char* INSTALL_DIR;
    char* BUILD_CMD;
};

void MANIFEST_parse(char *);

extern struct build_settings_struct build_settings;

#endif //FASTINSTALL_MANIFEST_H
