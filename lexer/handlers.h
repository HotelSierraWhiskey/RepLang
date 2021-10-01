#ifndef HANDLERS_H
#define HANDLERS_H


#include "lexer.h"


extern void check_state(void);

extern void next_lexeme_index(void);



// Handlers
extern void handle_double_quote(void);

extern void handle_control_char(void);

extern void handle_operator_char(void);

extern void handle_relation(void);

extern void handle_comparison_or_relation(void);

extern void handle_alphanum_char(void);

extern void handle_integer_literal(void);

extern void handle_separator(void);


#endif