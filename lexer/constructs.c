#include "constructs.h"


char *keywords[] = {IF, THEN, ELSE, ENDIF, WHILE, REDO, ENDWHILE, LABEL, GOTO, LET, INPUT, SHOW};

char *comparisons[] = {EQUIV, NOT_EQ, GT_EQ, LT_EQ, GT, LT};

char *operators[] = {PLUS, MINUS, MULTIPLY, DIVIDE};

char *controls[] = {OPEN_PAREN, CLOSE_PAREN, OPEN_BRACKET, CLOSE_BRACKET};

char valid_comparison_start_chars[] = {'<', '>', '!', '='};

char valid_comparison_end_chars[] = {'='};
