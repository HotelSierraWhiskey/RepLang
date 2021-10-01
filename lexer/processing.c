#include "lexer.h"
#include "processing.h"
#include "utils.h"


void check_control_processing_complete(void) {
    switch(hash_key_from_lexeme(lexer->current_lexeme)) {
        case CONTROL_OPEN_PAREN:
            build_token(CONTROL_OPEN_PAREN);
            break;

        case CONTROL_CLOSE_PAREN:
            build_token(CONTROL_CLOSE_PAREN);
            break;

        case CONTROL_OPEN_BRACKET:
            build_token(CONTROL_OPEN_BRACKET);
            break;

        case CONTROL_CLOSE_BRACKET:
            build_token(CONTROL_CLOSE_BRACKET);
            break;
    }
}


void check_identifier_or_keyword_processing_complete(void) {
    if (is_keyword() && !isalnum(lexer->next_char) && lexer->next_char != *UNDERSCORE) {
        _check_keyword_processing_complete();
    }
    else {
        _check_identifier_processing_complete();
    }
}


void _check_keyword_processing_complete(void) {
    switch(hash_key_from_lexeme(lexer->current_lexeme)) {
        case STATEMENT_IF:
            build_token(STATEMENT_IF);
            break;

        case STATEMENT_ELSE:
            build_token(STATEMENT_ELSE);
            break;

        case STATEMENT_ENDIF:
            build_token(STATEMENT_ENDIF);
            break;

        case STATEMENT_WHILE:
            build_token(STATEMENT_WHILE);
            break;

        case STATEMENT_REDO:
            build_token(STATEMENT_REDO);
            break;

        case STATEMENT_ENDWHILE:
            build_token(STATEMENT_ENDWHILE);
            break;

        case STATEMENT_LABEL:
            build_token(STATEMENT_LABEL);
            break;

        case STATEMENT_GOTO:
            build_token(STATEMENT_GOTO);
            break;

        case STATEMENT_LET:
            build_token(STATEMENT_LET);
            break;

        case STATEMENT_INPUT:
            build_token(STATEMENT_INPUT);
            break;
    }
}


void _check_identifier_processing_complete(void) {
    char current = lexer->current_char;

    if (lexer->periods_seen > 0) {
        reset_current_lexeme();
        return;
    }

    if (!strcmp(&current, PERIOD)) {
        lexer->periods_seen++;
        return;
    }

    if (!isalnum(current) && strcmp(&current, UNDERSCORE) && lexer->periods_seen == 0) {
        build_token(IDENTIFIER);
    }
}


void check_integer_or_float_literal_processing_complete(void) {
    
    char current = lexer->current_char;

    if (!isdigit(current) && strcmp(&current, PERIOD)) {
        if (lexer->periods_seen > 1) {
            reset_current_lexeme();
            return;
        }
        if (lexer->periods_seen == 1) {
            build_token(FLOAT_LITERAL);
            lexer->periods_seen = 0;
            return;
        }
        if (lexer->periods_seen == 0 && *lexer->current_lexeme != *PERIOD) {
            build_token(INTEGER_LITERAL);
            return;
        }
    } 
}


void check_operator_processing_complete(void) {
    // lexer->periods_seen = 0;

    switch(hash_key_from_lexeme(lexer->current_lexeme)) {
        case OPERATOR_PLUS:
            build_token(OPERATOR_PLUS);
            break;

        case OPERATOR_MINUS:
            build_token(OPERATOR_MINUS);
            break;

        case OPERATOR_MULTIPLY:
            build_token(OPERATOR_MULTIPLY);
            break;

        case OPERATOR_DIVIDE:
            build_token(OPERATOR_DIVIDE);
            break;
    }
}


void check_comparison_or_relation_processing_complete(void) {
    // lexer->periods_seen = 0;
    switch(hash_key_from_lexeme(lexer->current_lexeme)) {
            case COMPARISON_NOT_EQ:
                build_token(COMPARISON_NOT_EQ);
                break;

            case COMPARISON_EQUIV:
                build_token(COMPARISON_EQUIV);
                break;

            case COMPARISON_GT_EQ: 
                build_token(COMPARISON_GT_EQ);
                break;

            case COMPARISON_LT_EQ: 
                build_token(COMPARISON_LT_EQ);
                break;
        }

    if (lexer->next_char != *EQUALS) {
        switch(hash_key_from_lexeme(lexer->current_lexeme)) {
            case COMPARISON_NOT_EQ:
                build_token(COMPARISON_NOT_EQ);
                break;

            case RELATION:
                build_token(RELATION);
                break;
                
            case COMPARISON_GT: 
                build_token(COMPARISON_GT);
                break;

            case COMPARISON_LT: 
                build_token(COMPARISON_LT);
                break;

            default: reset_current_lexeme();
        }
    }
}


void check_string_literal_processing_complete(void) {
    if (lexer->state == FINISHED_STRING_LITERAL_PROCESSING)
        build_token(STRING_LITERAL);
}


void check_separator_processing_complete(void) {
    lexer->periods_seen = 0;
    build_token(SEPARATOR);
}