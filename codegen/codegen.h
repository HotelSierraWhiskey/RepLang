#ifndef CODEGEN_H
#define CODEGEN_H


typedef void (* emit_function_t)(const char *);


typedef struct {
    char *buffer;
    uint32_t buffer_size;
    emit_function_t emit;
} emitter_t;

emitter_t emitter;

extern void run_codegen(void);

extern void emitter_init(void);

extern void emit(const char *code);



#endif