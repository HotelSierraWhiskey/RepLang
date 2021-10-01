#ifndef UTILS_H
#define UTILS_H


#define print_current_lexeme() printf("current lexeme: %s\n", lexer->current_lexeme)
#define print_current_char() printf("current char: %c\n", lexer->current_char)


extern void reset_current_lexeme(void);

extern bool is_keyword(void);

extern bool is_double_quote(void);

extern bool is_operator_char(void);

extern bool is_control_char(void);

extern bool is_relation_char(void);

extern bool is_comparison_char(void);

extern bool is_separator_char(void);

extern bool is_alphanum_char(void);

extern bool is_digit_char(void);


#endif