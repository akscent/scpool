#ifndef STACK_H
#define STACK_H
#define EMPTY_STACK -1

typedef struct node {
    int data;
    struct node* next;
} node_t;

typedef struct {
    node_t* top;
} stack_ti;

stack_ti* init();
void push(stack_ti* s, int data);
int pop(stack_ti* s);
void destroy(stack_ti* s);

#endif
