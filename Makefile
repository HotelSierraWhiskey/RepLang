cc=GCC

run:
	gcc ./lexer/lexer.c ./lexer/lexer_subsystem.c ./lexer/handlers.c ./lexer/processing.c ./lexer/constructs.c ./lexer/utils.c \
	./parser/parser.c ./parser/parse_utils.c \
	debug.c system.c errors.c main.c -o rep && \
	./rep ./tests/sample_1.txt -ldebug -pdebug

clean:
	rm -rf ./rep

remake:
	make clean && make run