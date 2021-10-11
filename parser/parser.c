#include "../debug.h"
#include "../codegen/codegen.h"
#include "parser.h"


void rule_statement(void) {
    // Naked comparison, identifier, or literal expression
    if (check_token(INTEGER_LITERAL) || \
        check_token(FLOAT_LITERAL) || check_token(STRING_LITERAL)) {
        emit(parser.current_token->contents);
        next_token(__func__);
        rule_expression();
    }

    else if (check_token(STATEMENT_SHOW)) {
        emit("print");
        next_token(__func__);
        rule_expression();
    }

    //  let statement
    else if (check_token(STATEMENT_LET)) {
        next_token(__func__);

        emit(parser.current_token->contents);
        match(IDENTIFIER);
        add_identifier(parser.current_token->contents);
        next_token(__func__);

        emit(parser.current_token->contents);
        match(RELATION);
        next_token(__func__);

        rule_expression();
    }

    // variable reassignment expression
    else if (check_token(IDENTIFIER) && is_identifier()) {
        emit(parser.current_token->contents);
        next_token(__func__);

        match(RELATION);
        emit(parser.current_token->contents);
        next_token(__func__);
        rule_expression();
    }

    // if -> then -> endif
    else if (check_token(STATEMENT_IF)) {
        emit("if ");
        next_token(__func__);
        rule_comparison();

        match(STATEMENT_THEN);
        next_token(__func__);

        while (!check_token(STATEMENT_ENDIF)) {
            rule_statement();
        }
        match(STATEMENT_ENDIF);
        next_token(__func__);
    }

    // while -> endwhile
    else if (check_token(STATEMENT_WHILE)) {
        emit("while ");
        next_token(__func__);
        rule_comparison();

        while (!check_token(STATEMENT_ENDWHILE)) {
            rule_statement();
        }
        match(STATEMENT_ENDWHILE);
        next_token(__func__);
    }
    else if (check_token(STATEMENT_LABEL)) {
        next_token(__func__);
        match(IDENTIFIER);
        next_token(__func__);
    }

    else if (check_token(STATEMENT_GOTO)) {
        next_token(__func__);
        match(IDENTIFIER);
        next_token(__func__);
    }

    // loop statement
    else if (check_token(STATEMENT_LOOP)) {
        parser.state = PARSER_PROCESSING_LOOP_STATEMENT_STATE;
        emit("for ");
        next_token(__func__);
        match(CONTROL_OPEN_PAREN);
        parser.paren_depth++;
        parser.tab_depth++;
        next_token(__func__);
        match(INTEGER_LITERAL);
        char *iter_var = malloc(sizeof(char) * strlen(parser.current_token->contents));
        strcpy(iter_var, parser.current_token->contents);
        next_token(__func__);

        match(IDENTIFIER);
        char *loop_var = malloc(sizeof(char) * strlen(parser.current_token->contents));
        strcpy(loop_var, parser.current_token->contents);

        emit(loop_var);
        emit(" in range(");
        emit(iter_var);
        next_token(__func__);
    }

    else if (check_token(STATEMENT_ENDLOOP)) {
        parser.state = PARSER_PROCESSING_ENDLOOP_STATEMENT_STATE;
        parser.tab_depth--;
        next_token(__func__);
    }


    // Balance parens
    while (parser.paren_depth > 0) {
        rule_expression();
        emit(")");
        match(CONTROL_CLOSE_PAREN);
        next_token(__func__);
        parser.paren_depth--;
    }


    if (parser.state == PARSER_PROCESSING_LOOP_STATEMENT_STATE) {
        emit(":");
    }

    rule_separator();
    emit("\n");

    for (uint8_t i = 0; i < parser.tab_depth; i++) {
        emit("\t");
    }

    parser.state = PARSER_WAITING_STATE;
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
        emit(parser.current_token->contents);
        next_token(__func__);
        rule_expression();
    }
    while (is_comparison_operator()) {
        emit(parser.current_token->contents);
        next_token(__func__);
        rule_expression();
    }
}


void rule_expression(void) {
    rule_term();

    while (check_token(CONTROL_OPEN_PAREN)) {
        parser.paren_depth++;
        emit(parser.current_token->contents);
        next_token(__func__);
        rule_expression();
    }

    while (is_comparison_operator()) {
        emit(parser.current_token->contents);
        next_token(__func__);
        rule_expression();
    }

    while (check_token(OPERATOR_PLUS) || check_token(OPERATOR_MINUS)) {
        emit(parser.current_token->contents);
        next_token(__func__);
        rule_term();
    }
}


void rule_term(void) {
    if (check_token(STRING_LITERAL)) {
        emit(parser.current_token->contents);
        next_token(__func__);
    }
    rule_unary();
    while (check_token(OPERATOR_MULTIPLY) || check_token(OPERATOR_DIVIDE)) {
        emit(parser.current_token->contents);
        next_token(__func__);
        rule_unary();
    }
}


void rule_unary(void) {
    if (check_token(OPERATOR_PLUS) || check_token(OPERATOR_MINUS)) {
        emit(parser.current_token->contents);
        next_token(__func__);
    }
    rule_primary();
}


void rule_primary(void) {
    if (check_token(INTEGER_LITERAL) || check_token(FLOAT_LITERAL)) {
        emit(parser.current_token->contents);
        next_token(__func__);
    }
    else if (check_token(IDENTIFIER)) {
        emit(parser.current_token->contents);
        next_token(__func__);
    }
}


void rule_separator(void) {
    match(SEPARATOR);
    next_token(__func__);
    while (check_token(SEPARATOR))
        next_token(__func__);
}


void run_parser(void) {

    parser.current_token = lexer->token_table;
    parser.peek_token = lexer->token_table + 1;

    parser.state = WAITING_STATE;

    while (parser.current_token->contents != NULL) {
        rule_statement();
    }
}