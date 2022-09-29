/*
Copyright (c) 2015 - 2022 Michael Steinmötzger

All rights are reserved for this project, unless otherwise
stated in a license file.
*/

#ifndef FASTINSTALL_LOG_UTIL_H
#define FASTINSTALL_LOG_UTIL_H
#define LOG(...) printf("[%s:%d] %sLOG:%s ", __func__, __LINE__, GRN, reset); \
                 printf(__VA_ARGS__)

#define LOG_LN(...) printf("[%s:%d] %sLOG:%s ", __func__, __LINE__, GRN, reset); \
                 printf(__VA_ARGS__);               \
                 printf("\n")

#define WARN(...) printf("[%s:%d] %sWARN:%s ", __func__, __LINE__, YEL, reset); \
                 printf(__VA_ARGS__)

#define WARN_LN(...) printf("[%s:%d] %sWARN:%s ", __func__, __LINE__, YEL, reset); \
                 printf(__VA_ARGS__);               \
                 printf("\n")

#define ERR(...) printf("[%s:%d] %sERR:%s ", __func__, __LINE__, RED, reset); \
                 printf(__VA_ARGS__)

#define ERR_LN(...) printf("[%s:%d] %sERR:%s ", __func__, __LINE__, RED, reset); \
                 printf(__VA_ARGS__);               \
                 printf("\n")

#define DBG(...) printf("[%s:%d] %sDEBUG:%s ", __func__, __LINE__, CYN, reset); \
                 printf(__VA_ARGS__)

#define DBG_LN(...) printf("[%s:%d] %sDEBUG:%s ", __func__, __LINE__, CYN, reset); \
                 printf(__VA_ARGS__);               \
                 printf("\n")

#endif //FASTINSTALL_LOG_UTIL_H
