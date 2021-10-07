#ifndef SYSTEM_H
#define SYSTEM_H


typedef struct {
    char *target_filename;
    char *out_filename;
} system_info_t;

extern system_info_t system_info;


extern void system_init(char** argv);

#endif