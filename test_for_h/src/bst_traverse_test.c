#include <stdio.h>

#include "bst.h"

// test bstree_apply_infix function
int main() {
    // create test tree
    t_btree* root = bstree_create_node(5);
    bstree_insert(root, 3, &cmpf);
    bstree_insert(root, 8, &cmpf);
    bstree_insert(root, 2, &cmpf);
    bstree_insert(root, 4, &cmpf);
    bstree_insert(root, 7, &cmpf);
    bstree_insert(root, 9, &cmpf);

    // test bstree_apply_infix function
    printf("bstree_apply_infix test: expected output is '2 3 4 5 7 8 9'\nOutput: ");
    bstree_apply_infix(root, &print_node);
    printf("success\n");

    // test bstree_apply_prefix function
    printf("bstree_apply_prefix test: expected output is '5 3 2 4 8 7 9'\nOutput: ");
    bstree_apply_prefix(root, &print_node);
    printf("success\n");

    // test bstree_apply_postfix function
    printf("bstree_apply_postfix test: expected output is '2 4 3 7 9 8 5'\nOutput: ");
    bstree_apply_postfix(root, &print_node);
    printf("success\n");

    // cleanup
    bstree_free(root);

    return 0;
}
