#include "../debug.h"
#include "parser.h"


void rule_statement(void) {
    // Naked comparison, identifier, or literal expression
    if (check_token(IDENTIFIER) || check_token(INTEGER_LITERAL) || \
        check_token(FLOAT_LITERAL) || check_token(STRING_LITERAL)) {
        next_token(__func__);
        rule_expression();
    }

    //  let statement
    else if (check_token(STATEMENT_LET)) {
        next_token(__func__);
        match(IDENTIFIER);
        next_token(__func__);
        rule_expression();
    }

    // if -> then -> endif
    else if (check_token(STATEMENT_IF)) {
        next_token(__func__);
        rule_comparison();

        match(STATEMENT_THEN);

        while (!check_token(STATEMENT_ENDIF)) {
            rule_statement();
        }
        match(STATEMENT_ENDIF);
    }

    // while -> endwhile
    else if (check_token(STATEMENT_WHILE)) {
        next_token(__func__);
        rule_comparison();

        while (!check_token(STATEMENT_ENDWHILE)) {
            rule_statement();
        }
        match(STATEMENT_ENDWHILE);
    }
    else if (check_token(STATEMENT_LABEL)) {
        next_token(__func__);
        match(IDENTIFIER);
    }

    else if (check_token(STATEMENT_GOTO)) {
        next_token(__func__);
        match(IDENTIFIER);
    }

    // Balance parens
    // next_token(__func__);
    while (parser.paren_depth > 0) {
        rule_expression();
        match(CONTROL_CLOSE_PAREN);
        parser.paren_depth--;
    }

    rule_separator();
}


bool is_comparison_operator(void) {
    for (char **cmp = comparisons; *cmp != NULL; cmp++) {
        if (!strcmp(*cmp, parser.current_token->contents)) {
            return true;
        }
    }
    return false;
}


void rule_comparison(void) {
    rule_expression();

    if (is_comparison_operator()) {
        next_token(__func__);
        rule_expression();
    }
    while (is_comparison_operator()) {
        next_token(__func__);
        rule_expression();
    }
}


void rule_expression(void) {
    rule_term();

    while (check_token(CONTROL_OPEN_PAREN)) {
        parser.paren_depth++;
        next_token(__func__);
        rule_expression();
    }

    while (is_comparison_operator()) {
        next_token(__func__);
        rule_expression();
    }

    while (check_token(OPERATOR_PLUS) || check_token(OPERATOR_MINUS)) {
        next_token(__func__);
        rule_term();
    }
}


void rule_term(void) {
    rule_unary();
    while (check_token(OPERATOR_MULTIPLY) || check_token(OPERATOR_DIVIDE)) {
        next_token(__func__);
        rule_unary();
    }
}


void rule_unary(void) {
    if (check_token(OPERATOR_PLUS) || check_token(OPERATOR_MINUS)) {
        next_token(__func__);
    }
    rule_primary();
}


void rule_primary(void) {
    if (check_token(INTEGER_LITERAL) || check_token(FLOAT_LITERAL)) {
        next_token(__func__);
    }
    else if (check_token(IDENTIFIER)) {
        next_token(__func__);
    }
}


void rule_separator(void) {
    match(SEPARATOR);
    while (check_token(SEPARATOR))
        next_token(__func__);
}


void run_parser(void) {

    parser.current_token = lexer->token_table;
    parser.peek_token = lexer->token_table + 1;

    while (parser.current_token->contents != NULL) {
        // printf("%s\n", parser.current_token->contents);
        // next_token(__func__);
        rule_statement();
    }
}