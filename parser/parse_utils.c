#include "../errors.h"
#include "parser.h"


void next_token(const char *caller_name) {
    debug.trace_callback(caller_name);
    parser.current_token = parser.peek_token;
    parser.peek_token++;
}


bool check_token(token_type_t type) {
    return parser.current_token->type == type;
}


bool check_tokens(token_type_t *types) {
    for (token_type_t *t = types; t != NULL; t++) {
        if (check_token(*t)) {
            return true;
        }
    }
    return false;
}


bool check_peek(token_type_t type) {
    return parser.peek_token->type == type;
}


void match(token_type_t type) {
    if (!check_token(type)) {
        error_parser_token_mismatch(type);
        exit(0);
    }
    // next_token(__func__);
}