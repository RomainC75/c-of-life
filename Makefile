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