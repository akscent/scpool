CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
SRC = *.c

.PHONY: all clean format

all: database

database: $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o Database

clean:
	rm -f $(BUILD_DIR)

format:
	clang-format -i -style="{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 110}" $(SRC)

