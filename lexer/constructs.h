#ifndef CONSTRUCTS_H
#define CONSTRUCTS_H

extern char valid_comparison_start_chars[];

extern char valid_comparison_end_chars[];


// KEYWORDS
#define MAX_KEYWORDS 16
extern char *keywords[];

// SEPARATORS
#define ENDLINE ";"

// RELATION
#define EQUALS "="

// OPERATORS
#define PLUS "+"
#define MINUS "-"
#define MULTIPLY "*"
#define DIVIDE "/"
extern char *operators[];

// COMPARISONS
#define EQUIV "=="
#define NOT_EQ "!="
#define GT_EQ ">="
#define LT_EQ "<="
#define GT ">"
#define LT "<"
extern char *comparisons[];

// STATEMENTS
#define IF "if"
#define ELSE "else"
#define ENDIF "endif"
#define WHILE "while"
#define REDO "redo"
#define ENDWHILE "endwhile"
#define LABEL "label"
#define GOTO "goto"
#define LET "let"
#define INPUT "input"
extern char *statements[];

// STRING LITERAL
#define DOUBLE_QUOTE '"'

// CONTROLS
#define OPEN_PAREN "("
#define CLOSE_PAREN ")"
#define OPEN_BRACKET "["
#define CLOSE_BRACKET "]"
extern char *controls[];

// SPECIAL CHARS
#define UNDERSCORE "_"
#define HYPHEN "-"
#define PERIOD "."


#endif