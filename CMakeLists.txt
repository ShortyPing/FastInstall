cmake_minimum_required(VERSION 3.24)
project(FastInstall C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_STANDARD 99)

add_executable(FastInstall src/main.c src/utils/args_util.h src/utils/log_util.c src/utils/log_util.h src/utils/color.h src/manifest.c src/manifest.h src/const.h src/install.c src/install.h)
