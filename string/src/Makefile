CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
BUILD_DIR = ../build
SRC = s21_string.c s21_string_test.c

.PHONY: all clean format

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_test strstr_test strtok_test

strlen_tests: $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -D STRLEN $^ -o $(BUILD_DIR)/Quest_1

strcmp_tests: $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -DSTRCMP -DTEST_CASE=s21_strcmp_test $^ -o $(BUILD_DIR)/Quest_2

strcpy_tests: $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -DSTRCPY -DTEST_CASE=s21_strcpy_test $^ -o $(BUILD_DIR)/Quest_3

strcat_tests: $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -DSTRCAT -DTEST_CASE=s21_strcat_test $^ -o $(BUILD_DIR)/Quest_4

strchr_test: $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -DSTRCHR -DTEST_CASE=s21_strchr_test $^ -o $(BUILD_DIR)/Quest_5

strstr_test: $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -DSTRSTR -DTEST_CASE=s21_strstr_test $^ -o $(BUILD_DIR)/Quest_6

strtok_test: $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -DSTRTOK -DTEST_CASE=s21_strtok_test $^ -o $(BUILD_DIR)/Quest_7

clean:
	rm -rf $(BUILD_DIR)

format:
	clang-format -i -style="{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 110}" $(SRC)