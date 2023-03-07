CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
BUILD_DIR = ../build
#SRC1 = documentation_module.c main_module_entry_point.c
SRC = print_module.c main_module_entry_point.c
#SRC2 = bst_create_test.c bst.c
#SRC3 = bst_insert_test.c bst.c
#SRC4 = bst_traverse_test.c bst.c

.PHONY: all clean format

all: print_module 

print_module: $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -D LOG $^ -o $(BUILD_DIR)/Quest_1

clean:
	rm -f $(BUILD_DIR)

format:
	clang-format -i -style="{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 110}" $(SRC) 