#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"
#include "grammar.h"


typedef struct {
    token_t list[MAX_EXPR_SIZE];
    uint8_t size;
} expr_t;


// extern expr_t identifier_expected_types;
// extern expr_t keyword_expected_types;
// extern expr_t separator_expected_types;
// extern expr_t operator_expected_types;
// extern expr_t relation_expected_types;
// extern expr_t control_expected_types; 
// extern expr_t string_literal_expected_types;
// extern expr_t integer_literal_expected_types;




typedef struct {
    // expr_t *expecting;
    token_t *current_token;
    token_t *peek_token;

    // expr_t expressions[MAX_ENUM_EXPRS];
    // uint32_t expr_index;
    // uint32_t token_index;
    // bool expr_complete;
} parser_t;

parser_t parser;


// typedef struct _node_t {
//     token_t *token;
//     struct _node_t *left;
//     struct _node_t *right;
// } node_t;

// extern node_t *root;



extern void run_parser(void);

extern void next_token(void);

extern bool check_token(token_type_t type);

extern bool check_peek(token_type_t type);

extern bool match(token_type_t type);




void rule_statement(void);

void rule_separator(void);

void rule_comparison(void);

void rule_expression(void);

void rule_term(void);

void rule_unary(void);

void rule_primary(void);





// extern void tree_insert(token_t *token);

// extern void pre_order_traversal(node_t *root);

// extern void in_order_traversal(node_t *root);

// extern void post_order_traversal(node_t *root);

// void print_t(node_t *tree);


#endif