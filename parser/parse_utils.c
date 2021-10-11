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
}


void add_identifier(const char *name) {
    if (!parser.identifier_bank.identifiers) {
        parser.identifier_bank.identifiers = malloc(sizeof(char **) + 17); // <-- why 17?
    }
    *(parser.identifier_bank.identifiers + parser.identifier_bank.num_entries) = malloc(strlen(name));
    strcpy(*(parser.identifier_bank.identifiers + parser.identifier_bank.num_entries), name);
    parser.identifier_bank.num_entries++;
}


bool is_identifier(void) {
    for (uint32_t i = 0; i < parser.identifier_bank.num_entries; i++) {
        if (!strcmp(parser.current_token->contents, *(parser.identifier_bank.identifiers + i))) {
            return true;
        }
    }
    return false;
}