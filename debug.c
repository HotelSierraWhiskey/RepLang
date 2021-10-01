#include "debug.h"



const char *ldebug_filename = "lexer_debug.txt";
const char *pdebug_filename = "parser_debug.txt";

const char *ldebug_flag = "-ldebug";
const char *pdebug_flag = "-pdebug";


debug_t debug;


extern void set_debug_flags(char **argv) {
    for (char **c = argv; *c != NULL; c++) {
        if (!strcmp(*c, ldebug_flag)) {
            debug.lexer_subsystem = ON;
            printf("Note: lexer subsystem in debug mode. Generating %s...\n", ldebug_filename);
        }
        if (!strcmp(*c, pdebug_flag)) {
            debug.parser_subsystem = ON;
            printf("Note: parser subsystem in debug mode. Generating %s...\n", pdebug_filename);
        }
    }
}
