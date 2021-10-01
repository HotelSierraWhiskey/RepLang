#ifndef PROCESSING_H
#define PROCESSING_H


extern void check_state(void);

extern void _check_identifier_processing_complete(void);

extern void check_identifier_or_keyword_processing_complete(void);

extern void check_integer_or_float_literal_processing_complete(void);

extern void check_string_literal_processing_complete(void);

extern void check_separator_processing_complete(void);

extern void check_operator_processing_complete(void);

extern void check_control_processing_complete(void);

extern void check_comparison_or_relation_processing_complete(void);

extern void _check_keyword_processing_complete(void);


#endif