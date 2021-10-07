#ifndef LEXER_H
#define LEXER_H


#include "../includes.h"
#include "../system.h"
#include "../debug.h"
#include "constructs.h"


#define MAX_TOKENS 512
#define MAX_LEXEME_SIZE 512


typedef enum {
    IDENTIFIER = 1,
    SEPARATOR,

    STATEMENT_IF,
    STATEMENT_THEN,
    STATEMENT_ELSE,
    STATEMENT_ENDIF,
    STATEMENT_WHILE,
    STATEMENT_REDO,
    STATEMENT_ENDWHILE,
    STATEMENT_LABEL,
    STATEMENT_GOTO,
    STATEMENT_LET,
    STATEMENT_INPUT,
    STATEMENT_PRINT,

    COMPARISON_EQUIV,
    COMPARISON_NOT_EQ,
    COMPARISON_GT_EQ,
    COMPARISON_LT_EQ,
    COMPARISON_GT,
    COMPARISON_LT,

    OPERATOR_PLUS,
    OPERATOR_MINUS,
    OPERATOR_MULTIPLY,
    OPERATOR_DIVIDE,

    CONTROL_OPEN_PAREN,
    CONTROL_CLOSE_PAREN,
    CONTROL_OPEN_BRACKET,
    CONTROL_CLOSE_BRACKET,

    STRING_LITERAL,
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    CONTROL,
    RELATION,
} token_type_t;


typedef enum {
    WAITING_STATE,
    PROCESSING_STRING_LITERAL,
    FINISHED_STRING_LITERAL_PROCESSING,
    PROCESSING_SEPARATOR,
    PROCESSING_INTEGER_OR_FLOAT_LITERAL,
    PROCESSING_IDENTIFIER_OR_KEYWORD,
    PROCESSING_OPERATOR,
    PROCESSING_COMPARISON_OR_RELATION,
    PROCESSING_CONTROL
} lexer_state_t;

typedef struct {
    token_type_t type;
    char *contents;
} token_t;


typedef struct {
    lexer_state_t state;
    char next_char;
    char current_char;
    uint8_t periods_seen;
    char current_lexeme[MAX_LEXEME_SIZE];
    uint8_t lexeme_index;
    token_t token_table[MAX_TOKENS];
    uint8_t table_index;
} lexer_t;

extern lexer_t *lexer;


typedef struct {
    token_type_t key;
    char *value;
} hash_t;


void run_lexical_analysis(void);

void process_line(char *line_buffer);

void process_char(char *current);

void build_token(token_type_t type);

extern char *hash_token_type(token_type_t type);

extern token_type_t hash_key_from_lexeme(char *lexeme);


#endif