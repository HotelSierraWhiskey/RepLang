#ifndef ERRORS_H
#define ERRORS_H


#include "lexer/lexer.h"

void error_file_not_found(void);

void error_parser_token_mismatch(token_type_t expected);

void note_debug_output_file(const char *subsystem_name, const char *filename);

void note_trace_flag_set(void);

#endif