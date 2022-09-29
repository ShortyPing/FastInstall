/*
Copyright (c) 2015 - 2022 Michael Steinmötzger

All rights are reserved for this project, unless otherwise
stated in a license file.
*/

#ifndef FASTINSTALL_ARGS_UTIL_H
#define FASTINSTALL_ARGS_UTIL_H

#define CHECK_ARG(x, y) if(!strcmp(argv[i], x) || !strcmp(argv[i], y))
#define CHECK_NEXT_ARG  if(argc <= i+1) { \
                            ERR_LN("Expected value for parameter \"%s\"", ARG); \
                            exit(1);                  \
                        }                 \
                        if(NEXT_ARG[0] == '-') {                               \
                            ERR_LN("Value for parameter \"%s\" cannot be a parameter definition", ARG); \
                            exit(1);                  \
                        }
#define ARG argv[i]
#define NEXT_ARG argv[i+1]

#endif //FASTINSTALL_ARGS_UTIL_H
