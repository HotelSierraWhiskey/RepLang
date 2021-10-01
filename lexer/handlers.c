#include "handlers.h"
#include "processing.h"
#include "utils.h"



void next_lexeme_index(void) {
    lexer->current_lexeme[lexer->lexeme_index] = lexer->current_char;
    lexer->lexeme_index++;
    lexer->current_char = lexer->next_char;
}


void check_state(void) {
    switch(lexer->state) {
        case WAITING_STATE:
            break;

        case FINISHED_STRING_LITERAL_PROCESSING:
            check_string_literal_processing_complete();
            break;

        case PROCESSING_INTEGER_OR_FLOAT_LITERAL:
            check_integer_or_float_literal_processing_complete();
            break;

        case PROCESSING_IDENTIFIER_OR_KEYWORD:
            check_identifier_or_keyword_processing_complete();
            break;

        case PROCESSING_SEPARATOR:
            check_separator_processing_complete();
            break;

        case PROCESSING_OPERATOR:
            check_operator_processing_complete();
            break;

        case PROCESSING_COMPARISON_OR_RELATION:
            check_comparison_or_relation_processing_complete();
            break;
        
        case PROCESSING_CONTROL:
            check_control_processing_complete();
            break;
    }
}


void handle_comparison_or_relation(void) {
    if (lexer->state == PROCESSING_STRING_LITERAL) {
        return;
    }
    lexer->state = PROCESSING_COMPARISON_OR_RELATION;
}


void handle_operator_char(void) {
    if (lexer->state == PROCESSING_STRING_LITERAL) {
        return;
    }
    lexer->state = PROCESSING_OPERATOR;
}


void handle_double_quote(void) {
    if (lexer->state != PROCESSING_STRING_LITERAL) {
        lexer->state = PROCESSING_STRING_LITERAL;
    }
    else {
        lexer->state = FINISHED_STRING_LITERAL_PROCESSING;
    }
}


void handle_control_char(void) {
if (lexer->state == PROCESSING_STRING_LITERAL) {
        return;
    }
    else {
        lexer->state = PROCESSING_CONTROL;
    }
}


void handle_alphanum_char(void) {
    char current = lexer->current_char;
    
    if (lexer->state == PROCESSING_STRING_LITERAL) {
        lexer->periods_seen = 0;
        return;
    }

    if (isalpha(current) && lexer->periods_seen == 0) { // && lexer->periods_seen == 0
        lexer->state = PROCESSING_IDENTIFIER_OR_KEYWORD;
        // lexer->periods_seen = 0;
        return;
    }

    if (isdigit(current) && lexer->state != PROCESSING_IDENTIFIER_OR_KEYWORD) {
        // lexer->periods_seen = 0;
        lexer->state = PROCESSING_INTEGER_OR_FLOAT_LITERAL;
        return;
    }
}


void handle_separator(void) {
    reset_current_lexeme();
    lexer->periods_seen = 0;
    lexer->state = PROCESSING_SEPARATOR;
}