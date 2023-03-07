#include "stack.h"

#include <stdio.h>
#define SUCCESS 0
#define FAIL 1

int test_push() {
    int success = SUCCESS;
    stack_ti* s = init();
    push(s, 5);
    push(s, 10);
    if (pop(s) != 10) {
        success = FAIL;
    }
    if (pop(s) != 5) {
        success = FAIL;
    }
    destroy(s);
    return success;
}

int test_pop() {
    int success = SUCCESS;
    stack_ti* s = init();
    push(s, 5);
    push(s, 10);
    if (pop(s) != 10) {
        success = FAIL;
    }
    if (pop(s) != 5) {
        success = FAIL;
    }
    if (pop(s) != EMPTY_STACK) {
        success = FAIL;
    }
    destroy(s);
    return success;
}

int main() {
    int success = SUCCESS;
    if (test_push() == FAIL) {
        printf("FAIL");
        success = FAIL;
    }
    if (test_pop() == FAIL) {
        printf("FAIL");
        success = FAIL;
    }
    if (success == SUCCESS) {
        printf("SUCCESS");
    }
    return success;
}