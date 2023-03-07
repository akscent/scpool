#include "stack.h"

#include <stdlib.h>

stack_ti* init() {
    stack_ti* s = (stack_ti*)malloc(sizeof(stack_ti));
    s->top = NULL;
    return s;
}

void push(stack_ti* s, int data) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = s->top;
    s->top = new_node;
}

int pop(stack_ti* s) {
    if (s->top == NULL) {
        return EMPTY_STACK;
    }
    int data = s->top->data;
    node_t* temp = s->top;
    s->top = s->top->next;
    free(temp);
    return data;
}

void destroy(stack_ti* s) {
    while (s->top != NULL) {
        node_t* temp = s->top;
        s->top = s->top->next;
        free(temp);
    }
    free(s);
}
