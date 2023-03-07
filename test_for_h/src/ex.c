#include <stdio.h>
#include <string.h>

#include "bst.h"

int main() {
    // Create a binary search tree
    t_btree *root = bstree_create_node(4);
    bstree_insert(root, 2, &cmpf);
    bstree_insert(root, 1, &cmpf);
    bstree_insert(root, 3, &cmpf);
    bstree_insert(root, 6, &cmpf);
    bstree_insert(root, 5, &cmpf);
    bstree_insert(root, 7, &cmpf);

    // Test bstree_apply_infix
    char expected_infix[] = "1 2 3 4 5 6 7 ";
    char actual_infix[50];
    char *p = actual_infix;
    bstree_apply_infix(root, &print_node, &p);
    if (strcmp(expected_infix, actual_infix) == 0) {
        printf("Success: bstree_apply_infix\n");
    } else {
        printf("Fail: bstree_apply_infix\n");
    }

    // Test bstree_apply_prefix
    char expected_prefix[] = "4 2 1 3 6 5 7 ";
    char actual_prefix[50];
    p = actual_prefix;
    bstree_apply_prefix(root, &print_node, &p);
    if (strcmp(expected_prefix, actual_prefix) == 0) {
        printf("Success: bstree_apply_prefix\n");
    } else {
        printf("Fail: bstree_apply_prefix\n");
    }

    // Test bstree_apply_postfix
    char expected_postfix[] = "1 3 2 5 7 6 4 ";
    char actual_postfix[50];
    p = actual_postfix;
    bstree_apply_postfix(root, &print_node, &p);
    if (strcmp(expected_postfix, actual_postfix) == 0) {
        printf("Success: bstree_apply_postfix\n");
    } else {
        printf("Fail: bstree_apply_postfix\n");
    }

    return 0;
}