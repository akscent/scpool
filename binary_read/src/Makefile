
CFLAGS = -Wall -Wextra -Werror --std=c11


all: build

build: state_sort state_search clear_state


state_sort: format binary.o state_sort.c state_sort.h
	gcc $(CFLAGS) binary.o state_sort.c -o ../build/Quest_1


state_search: format binary.o state_search.c state_search.h
	gcc $(CFLAGS) binary.o state_search.c -o ../build/Quest_2


clear_state: format binary.o clear_state.c clear_state.h
	gcc $(CFLAGS) binary.o clear_state.c -o ../build/Quest_3




binary.o: binary.c binary.h
	gcc $(CFLAGS) -c binary.c


format: clean
	clang-format -n *.c *.h
	clang-format -i *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem ./


clean:
	rm -rf *.o
	rm -rf ../build/Quest*


update: format clean
	git add .
	git commit -a -m "fix"
	git push
