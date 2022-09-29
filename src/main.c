/*
Copyright (c) 2015 - 2022 Michael Steinmötzger

All rights are reserved for this project, unless otherwise
stated in a license file.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils/args_util.h"
#include "utils/log_util.h"
#include "utils/color.h"

#include "manifest.h"

int main(int argc, char** argv) {

    char* m_file = "manifest.fi";

    for(unsigned i = 1; i < argc; i++) {

        CHECK_ARG("-m", "--manifest") {
            CHECK_NEXT_ARG
            m_file = NEXT_ARG;
        }
    }

    MANIFEST_parse(m_file);

    return 0;
}
