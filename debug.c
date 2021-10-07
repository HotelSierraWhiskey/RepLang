#include "errors.h"
#include "debug.h"
#include "system.h"
#include "lexer/lexer.h"
#include "parser/parser.h"



const char *ldebug_filename = "lexer_debug.txt";
const char *pdebug_filename = "parser_debug.txt";

const char *ldebug_flag = "-ldebug";
const char *pdebug_flag = "-pdebug";


debug_t debug;

void parser_trace_callback(const char *caller_name) {
    #ifdef PDEBUG
    printf("%-25s[token_type: %-18s\tcontents: %s]\n", caller_name, hash_token_type(parser.current_token->type), parser.current_token->contents);
    #endif
}


extern void set_debug_flags(char **argv) {

    debug.trace_callback = parser_trace_callback;

    printf("\nTarget file: %s\n", system_info.filename);
    
    #ifdef TRACE
    note_trace_flag_set();
    #endif

    for (char **c = argv; *c != NULL; c++) {
        if (!strcmp(*c, ldebug_flag)) {
            debug.lexer_subsystem = ON;
            note_debug_output_file("lexer", ldebug_filename);
        }
        if (!strcmp(*c, pdebug_flag)) {
            debug.parser_subsystem = ON;
            note_debug_output_file("parser", pdebug_filename);
        }
    }
}
