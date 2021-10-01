#include "parser.h"


#define print_token_hash(token_type) printf("[%s]\n", hash_token_type(token_type));



void rule_separator(void) {
    match(SEPARATOR);
    printf("separator\n");
    while (check_token(SEPARATOR))
        next_token();
}


void rule_statement(void) {
    if (check_token(IDENTIFIER)) {
        printf("identifier\n");
        next_token();

        rule_expression();
    }
    rule_separator();
}


bool is_comparison_operator(void) {
    for (char **cmp = comparisons; *cmp != NULL; cmp++) {
        printf("%s\t", *cmp);
        if (!strcmp(*cmp, parser.current_token->contents)) {
            return true;
        }
    }
    return false;
}


void rule_comparison(void) {
    printf("comparison\n");
    rule_expression();
    if (is_comparison_operator()) {
        next_token();
        rule_expression();
    }
    // else fail
    while (is_comparison_operator()) {
        next_token();
        rule_expression();
    }
}


void rule_expression(void) {
    printf("expression\n");
    rule_term();
    while (check_token(OPERATOR_PLUS) || check_token(OPERATOR_MINUS)) {
        next_token();
        rule_term();
    }
}


void rule_term(void) {
    printf("term\n");
    rule_unary();
    while (check_token(OPERATOR_MULTIPLY) || check_token(OPERATOR_DIVIDE)) {
        next_token();
        rule_unary();
    }
}



void rule_unary(void) {
    printf("unary\n");
    if (check_token(OPERATOR_PLUS) || check_token(OPERATOR_MINUS)) {
        next_token();
    }
    rule_primary();
}


void rule_primary(void) {
    printf("primary\n");
    if (check_token(INTEGER_LITERAL) || check_token(FLOAT_LITERAL)) {
        next_token();
    }
    else if (check_token(IDENTIFIER)) {
        next_token();
    }
}


void run_parser(void) {

    parser.current_token = lexer->token_table;
    parser.peek_token = lexer->token_table + 1;

    rule_statement();
}























// void build_expr(void) {
//     uint32_t *expr_idx = &parser.expr_index;
//     uint32_t *token_idx = &parser.token_index;
    
//     parser.expressions[*expr_idx].list[*token_idx].type = parser.current_token.type;
//     parser.expressions[*expr_idx].list[*token_idx].contents = malloc(sizeof(parser.current_token.type));
//     strcpy(parser.expressions[*expr_idx].list[*token_idx].contents, parser.current_token.contents);

//     if (parser.current_token.type == SEPARATOR) {
//         parser.expressions[*expr_idx].size = *token_idx + 1; // (plus one for the separator)
//         parser.expr_complete = true;
//         (*token_idx) = 0;
//         return;
//     }
//     parser.expr_complete = false;
//     (*token_idx)++;
// }



// bool look_ahead_valid(token_t *next_token) {
//     for (uint8_t i = 0; i < parser.expecting->size; i++) {
//         if (next_token->type == parser.expecting->list[i].type) {
//             return true;;
//         }
//     }
//     if (next_token == NULL) {
//         return false;
//     }
//     printf("error: [%s] unexpected type\n", hash_token_type(next_token->type));
//     return false;
// }



// void print_expr(uint32_t idx) {
//     printf("Expression %d: ", idx + 1);
//     for (uint32_t i = 0; i < parser.expressions[idx].size; i++) {
//         printf("[%s ( %s )]", hash_token_type(parser.expressions[idx].list[i].type), parser.expressions[idx].list[i].contents);
//     }
//     printf("\n");
// }



// void consume(token_t *token) {
    
//     parser.current_token = *token;
//     parser.peek_token = *(token + 1);


//     if (parser.expr_complete)
//         parser.expr_index++;

//     switch(parser.current_token.type) {
//         case SEPARATOR:
//             parser.expecting = &separator_expected_types;
//             break;

//         case IDENTIFIER:
//             parser.expecting = &identifier_expected_types;
//             break;

//         case KEYWORD:
//             parser.expecting = &keyword_expected_types;
//             break;

//         case OPERATOR:
//             parser.expecting = &operator_expected_types;
//             break;

//         case RELATION:
//             parser.expecting = &relation_expected_types;
//             break;

//         case CONTROL:
//             parser.expecting = &control_expected_types;
//             break;

//         case STRING_LITERAL:
//             parser.expecting = &string_literal_expected_types;
//             break;

//         case INTEGER_LITERAL:
//             parser.expecting = &integer_literal_expected_types;
//             break;
//     }

//     build_expr();
// }