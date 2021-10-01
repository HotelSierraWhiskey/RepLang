#include "includes.h"
#include "errors.h"


void error_file_not_found(void) {
    printf("Error: file not found\n");
}


void note_debug_output_file(const char *subsystem_name, const char *filename) {
    printf("Note: %s in debug mode. Generating %s.\n", subsystem_name, filename);
}