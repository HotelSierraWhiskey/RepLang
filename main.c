#include "system.h"
#include "./lexer/lexer.h"
#include "./parser/parser.h"
#include "./codegen/codegen.h"
#include "errors.h"


int main(int argc, char** argv) {

    system_init(argv);

    run_lexical_analysis();

    run_parser();

    run_codegen();
}

