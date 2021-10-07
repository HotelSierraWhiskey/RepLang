cc=GCC
CFLAGS=-Wall

#	Compiles the entire project
compile:
	gcc -DTRACE ./lexer/lexer.c ./lexer/lexer_subsystem.c ./lexer/handlers.c ./lexer/processing.c ./lexer/constructs.c ./lexer/utils.c \
	./parser/parser.c ./parser/parse_utils.c \
	./codegen/codegen.c \
	debug.c system.c errors.c main.c -o rep


#	Compile and run executable against test_1.txt by default
run:
	make compile && ./rep ./tests/test_1.txt -ldebug -pdebug


#	Compile and specify a test file
run_test:
	make compile && ./rep $(filename) -ldebug -pdebug

clean:
	rm -rf ./rep

remake:
	make clean && make run