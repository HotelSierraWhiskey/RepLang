#ifndef DEBUG_H
#define DEBUG_H


#include "includes.h"


#define ON 1
#define OFF 0


const char *ldebug;
const char *pdebug;


typedef void (*trace_callback_t)(const char *);


typedef struct {
    uint8_t lexer_subsystem: 1;
    uint8_t parser_subsystem: 1;
    trace_callback_t trace_callback;
} debug_t;

extern debug_t debug;


extern void set_debug_flags(char **argv);


#endif