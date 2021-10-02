#include "includes.h"
#include "errors.h"
#include "parser/parser.h"


void error_file_not_found(void) {
    printf("Error: file not found\n");
}


void error_parser_token_mismatch(token_type_t expected) {
    printf("Error: got %s. expected %s \n", hash_token_type(parser.current_token->type), \
    hash_token_type(expected));
}


void note_debug_output_file(const char *subsystem_name, const char *filename) {
    printf("Note: %s in debug mode. Generating %s.\n", subsystem_name, filename);
}


void note_trace_flag_set(void) {
    printf("Note: TRACE flag is set\n");
}