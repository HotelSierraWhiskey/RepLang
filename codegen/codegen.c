#include "../includes.h"
#include "../system.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "codegen.h"


#define BUFFER_INCREMENT_SIZE 256
#define MAX_LINE_LENGTH 512


emitter_t emitter;


void emit(const char *code) {
    while (strlen(code) > emitter.buffer_size) {
        char *allocation = malloc(emitter.buffer_size);
        strcpy(allocation, emitter.buffer);
        emitter.buffer_size += BUFFER_INCREMENT_SIZE;
        emitter.buffer = malloc(emitter.buffer_size);
        memmove(emitter.buffer, allocation, strlen(allocation));
        free(allocation);
    }
    strcat(emitter.buffer, code);
    emitter.buffer_size -= strlen(code);
}


void emitter_init(void) {
    emitter.buffer = malloc(sizeof(char) * BUFFER_INCREMENT_SIZE);
    emitter.buffer_size = BUFFER_INCREMENT_SIZE;
    emitter.emit = emit;
}


void run_codegen(void) {
    FILE *fp;

    if (access(system_info.out_filename, F_OK) == 0) {
        remove(system_info.out_filename);
    }

    fp = fopen(system_info.out_filename, "a+");

    char *strip = strtok(emitter.buffer, "\n");

    while (strip) {
        char *line = malloc(MAX_LINE_LENGTH);
        strcpy(line, strip);
        strcat(line, "\n");
        fputs(line, fp);
        free(line);
        strip = strtok(NULL, "\n");
    }
}


