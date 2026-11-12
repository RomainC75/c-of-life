run:
	gcc -std=c11 -Wall -o program main.c domain/*.c && ./program

debug:
	gcc -std=c11 -fsanitize=address -Wall -o program main.c domain/*.c && ./program

test:
	gcc -std=c11 -Wall -Wextra domain/position.c domain/tests/test_position.c -o test && ./test

# Used by the VS Code debugger (.vscode/tasks.json)
SRC = main.c $(wildcard domain/*.c)
OBJ = $(patsubst %.c,build/%.o,$(SRC))

build/%.o: %.c
	@mkdir -p $(dir $@)
	clang -std=c11 -Wall -g -O0 -MMD -MP -c $< -o $@

build-debug: $(OBJ)
	clang $(OBJ) -o program && dsymutil program

.PHONY: run debug test build-debug

-include $(OBJ:.o=.d)
