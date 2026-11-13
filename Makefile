CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c99 -g

BUILD_DIR = build

DOMAIN_SRC = \
	domain/position.c \
	domain/dimension.c \
	domain/cell.c \
	domain/board.c

TEST_SRC = \
	domain/tests/test_position.c \
	domain/tests/test_board.c \
	domain/tests/test_runner.c

TEST_BIN = $(BUILD_DIR)/test_runner

run:
	gcc -std=c11 -Wall -o program main.c domain/*.c && ./program

debug:
	gcc -std=c11 -fsanitize=address -Wall -o program main.c domain/*.c && ./program

test2:
	gcc -std=c11 -Wall -Wextra $(DOMAIN_SRC) $(TEST_SRC) -o test && ./test


.PHONY: all test clean

all: test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(DOMAIN_SRC) $(TEST_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DOMAIN_SRC) $(TEST_SRC) -o $(TEST_BIN)

clean:
	rm -rf $(BUILD_DIR)

# Used by the VS Code debugger (.vscode/tasks.json) — do not remove
DEBUG_DIR = $(BUILD_DIR)/debug
DEBUG_SRC = main.c $(DOMAIN_SRC)
DEBUG_OBJ = $(patsubst %.c,$(DEBUG_DIR)/%.o,$(DEBUG_SRC))

$(DEBUG_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	clang -std=c11 -Wall -g -O0 -MMD -MP -c $< -o $@

build-debug: $(DEBUG_OBJ)
	clang $(DEBUG_OBJ) -o program && dsymutil program

.PHONY: build-debug

-include $(DEBUG_OBJ:.o=.d)
