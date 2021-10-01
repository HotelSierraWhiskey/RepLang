#include "lexer_subsystem.h"


extern void lexer_subsystem_init(void) {
    lexer = malloc(sizeof(lexer_t));
    lexer->state = WAITING_STATE;
}