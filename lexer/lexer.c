#include "handlers.h"
#include "utils.h"


#define MAX_LINE_BUFFER_SIZE 512


lexer_t *lexer;


void run_lexical_analysis(void) {
    FILE *fp;
    char line_buffer[MAX_LINE_BUFFER_SIZE]; 
    fp = fopen(system_info.target_filename, "a+");
    fprintf(fp, "%s", "\n");
    

    fp = fopen(system_info.target_filename, "r");

    while (fgets(line_buffer, MAX_LINE_BUFFER_SIZE, fp) != NULL) {
        process_line(line_buffer);
    }

    if (debug.lexer_subsystem == ON) {
        FILE *debug_fp;
        debug_fp = fopen("./lexer_debug.txt", "w");
        for (token_t *token = lexer->token_table; token->contents != NULL; token++) {
            sprintf(line_buffer, "%-25s%s\n", hash_token_type(token->type), token->contents);
            fputs(line_buffer, debug_fp);
        }
    }
}


void process_line(char *line_buffer) {
    for (char *current = line_buffer; *current != '\0'; current++) {
        process_char(current);
    }
}


void process_char(char *current) {

    lexer->current_char = *current;
    lexer->next_char = *(current + 1);

    if (!strcmp(&lexer->current_char, PERIOD)) {
        lexer->periods_seen++;
    }

    if (is_alphanum_char()) {
        handle_alphanum_char();
        next_lexeme_index();
        check_state();
        return;
    }

    if (is_double_quote()) {
        handle_double_quote();
        next_lexeme_index();
        check_state();
        return;
    }

    if (is_separator_char()) {
        handle_separator();
        next_lexeme_index();
        check_state();
        return;
    }

    if (is_comparison_char()) {
        handle_comparison_or_relation();
        next_lexeme_index();
        check_state();
        return;
    }
    
    if (is_operator_char()) {
        handle_operator_char();
        next_lexeme_index();
        check_state();
        return;
    }

    if (is_control_char()) {
        handle_control_char();
        next_lexeme_index();
        check_state();
        return;
    }
}


extern void build_token(token_type_t type) {
    token_t *token = malloc(sizeof(token_t));
    token->type = type;
    token->contents = malloc(sizeof(lexer->current_lexeme)); // was once +1
    strcpy(token->contents, lexer->current_lexeme);
    memset(lexer->current_lexeme, 0, MAX_LEXEME_SIZE);
    lexer->token_table[lexer->table_index] = *token;
    lexer->lexeme_index = 0;
    lexer->state = WAITING_STATE;
    lexer->table_index++;
}


hash_t key_repr_hash_table[] = {
    {IDENTIFIER,            "IDENTIFIER"},
    {SEPARATOR,             "SEPARATOR"},
    {CONTROL,               "CONTROL"},
    {STRING_LITERAL,        "STRING_LITERAL"},
    {INTEGER_LITERAL,       "INTEGER_LITERAL"},
    {FLOAT_LITERAL,         "FLOAT_LITERAL"},
    {OPERATOR_PLUS,         "OPERATOR_PLUS"},
    {OPERATOR_MINUS,        "OPERATOR_MINUS"},
    {OPERATOR_MULTIPLY,     "OPERATOR_MULTIPLY"},
    {OPERATOR_DIVIDE,       "OPERATOR_DIVIDE"},
    {STATEMENT_IF,          "STATEMENT_IF"},
    {STATEMENT_THEN,        "STATEMENT_THEN"},
    {STATEMENT_ELSE,        "STATEMENT_ELSE"},
    {STATEMENT_ENDIF,       "STATEMENT_ENDIF"},
    {STATEMENT_WHILE,       "STATEMENT_WHILE"},
    {STATEMENT_REDO,        "STATEMENT_REDO"},
    {STATEMENT_ENDWHILE,    "STATEMENT_ENDWHILE"},
    {STATEMENT_LABEL,       "STATEMENT_LABEL"},
    {STATEMENT_GOTO,        "STATEMENT_GOTO"},
    {STATEMENT_LET,         "STATEMENT_LET"},
    {STATEMENT_INPUT,       "STATEMENT_INPUT"},
    {STATEMENT_SHOW,        "STATEMENT_SHOW"},
    {STATEMENT_LOOP,        "STATEMENT_LOOP"},
    {STATEMENT_ENDLOOP,     "STATEMENT_ENDLOOP"},
    {COMPARISON_EQUIV,      "COMPARISON_EQUIV"},
    {COMPARISON_NOT_EQ,     "COMPARISON_NOT_EQ"},
    {COMPARISON_GT_EQ,      "COMPARISON_GT_EQ"},
    {COMPARISON_LT_EQ,      "COMPARISON_LT_EQ"},
    {COMPARISON_GT,         "COMPARISON_GT"},
    {COMPARISON_LT,         "COMPARISON_LT"},
    {RELATION,              "RELATION"},
    {CONTROL_OPEN_PAREN,    "CONTROL_OPEN_PAREN"},
    {CONTROL_CLOSE_PAREN,   "CONTROL_CLOSE_PAREN"},
    {CONTROL_OPEN_BRACKET,  "CONTROL_OPEN_BRACKET"},
    {CONTROL_CLOSE_BRACKET, "CONTROL_CLOSE_BRACKET"},
    {CONTROL_COMMA,         "CONTROL_COMMA"}
};


extern char *hash_token_type(token_type_t type) {
    for (hash_t *hash = key_repr_hash_table; hash != NULL; hash++) {
        if (type == hash->key)
            return hash->value;
    }
}


hash_t key_lexeme_hash_table[] = {
    {RELATION,              EQUALS},
    {OPERATOR_PLUS,         PLUS},
    {OPERATOR_MINUS,        MINUS},
    {OPERATOR_MULTIPLY,     MULTIPLY},
    {OPERATOR_DIVIDE,       DIVIDE},
    {STATEMENT_IF,          IF},
    {STATEMENT_THEN,        THEN},
    {STATEMENT_ELSE,        ELSE },
    {STATEMENT_ENDIF,       ENDIF},
    {STATEMENT_WHILE,       WHILE},
    {STATEMENT_REDO,        REDO},
    {STATEMENT_ENDWHILE,    ENDWHILE},
    {STATEMENT_LABEL,       LABEL},
    {STATEMENT_GOTO,        GOTO},
    {STATEMENT_LET,         LET},
    {STATEMENT_INPUT,       INPUT},
    {STATEMENT_SHOW,        SHOW},
    {STATEMENT_LOOP,        LOOP},
    {STATEMENT_ENDLOOP,     ENDLOOP},
    {COMPARISON_EQUIV,      EQUIV},
    {COMPARISON_NOT_EQ,     NOT_EQ},
    {COMPARISON_GT_EQ,      GT_EQ},
    {COMPARISON_LT_EQ,      LT_EQ},
    {COMPARISON_GT,         GT},
    {COMPARISON_LT,         LT},
    {CONTROL_OPEN_PAREN,    OPEN_PAREN},
    {CONTROL_CLOSE_PAREN,   CLOSE_PAREN},
    {CONTROL_OPEN_BRACKET,  OPEN_BRACKET},
    {CONTROL_CLOSE_BRACKET, CLOSE_BRACKET},
    {CONTROL_COMMA,         COMMA}
};


token_type_t hash_key_from_lexeme(char *lexeme) {
    for (uint8_t i = 0; i < sizeof(key_lexeme_hash_table)/sizeof(hash_t); i++) {
        if (!strcmp(lexeme, key_lexeme_hash_table[i].value))
            return key_lexeme_hash_table[i].key;
    }
}
