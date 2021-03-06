#include "system.h"
#include "debug.h"
#include "errors.h"
#include "./lexer/lexer_subsystem.h"
#include "./codegen/codegen.h"


system_info_t system_info;


void system_init(char **argv) {
    if (!argv[1]) {
        error_file_not_found();
        exit(0);
    }
    system_info.target_filename = argv[1];
    system_info.out_filename = "./out.py";
    set_debug_flags(argv);
    lexer_subsystem_init();
    emitter_init();
}