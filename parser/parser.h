#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"


typedef struct {
    token_t *current_token;
    token_t *peek_token;
    uint8_t paren_depth;
} parser_t;

parser_t parser;


extern void run_parser(void);

extern void next_token(const char *caller_name);

extern bool check_token(token_type_t type);

extern bool check_tokens(token_type_t *types);

extern bool check_peek(token_type_t type);

extern void match(token_type_t type);




void rule_statement(void);

void rule_separator(void);

void rule_comparison(void);

void rule_expression(void);

void rule_term(void);

void rule_unary(void);

void rule_primary(void);


#endif