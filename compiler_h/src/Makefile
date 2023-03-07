CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
BUILD_DIR = ../build
SRC = dmanager_module.c
SRC1 = list_test.c list.c
SRC2 = stack_test.c stack.c

.PHONY: all clean format

all: door_struct list_test stack_test

door_struct: $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/Quest_1

list_test: $(SRC1)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/Quest_2

stack_test: $(SRC2)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/Quest_3

clean:
	rm -f $(BUILD_DIR)

format:
	clang-format -i -style="{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 110}" $(SRC) $(SRC1) $(SRC2)

