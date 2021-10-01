#include "lexer.h"
#include "utils.h"


void reset_current_lexeme(void) {
    memset(lexer->current_lexeme, 0, MAX_LEXEME_SIZE);
    lexer->lexeme_index = 0;
}


extern bool is_alphanum_char(void) {
    char current = lexer->current_char;
    return isalnum(current) || !strcmp(&current, UNDERSCORE) || !strcmp(&current, PERIOD);
}


extern bool is_double_quote(void) {
    char current = lexer->current_char;
    return current == DOUBLE_QUOTE; 
}


extern bool is_separator_char(void) {
    char current = lexer->current_char;
    if (!strcmp(&current, ENDLINE)) {
        return true;
    }
    else {
        return false;
    }
}


extern bool is_digit_char(void) {
    char current = lexer->current_char;
    return isdigit(current);
}


extern bool is_keyword(void) {
    for (char **k = keywords; *k != NULL; k++) {
        if (!strcmp(*k, lexer->current_lexeme)) {
            return true;
        }
    }
    return false;
}


extern bool is_control_char(void) {

    char **op = controls;

    for (uint8_t i = 0; i < 4; i++) {
        for (char *j = *(op + i); *j != '\0'; j++) {
            if (lexer->current_char == *j) {
                return true;
            }
        }
    }
    return false;
}


extern bool is_operator_char(void) {

    char **op = operators;

    for (uint8_t i = 0; i < 4; i++) {
        for (char *j = *(op + i); *j != '\0'; j++) {
            if (lexer->current_char == *j) {
                return true;
            }
        }
    }
    return false;
}


bool is_comparison_char(void) {
    for (uint8_t i = 0; i < 4; i++) {
        if (lexer->current_char == valid_comparison_start_chars[i]) {
            return true;
        }
    }
    return false;
}