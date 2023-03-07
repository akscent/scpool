#include <stdio.h>

#include "bst.h"

int main() {
    // Test Case 1
    t_btree *root = NULL;

    // Test successful insertions
    bstree_insert(&root, 5, &cmpf);
    bstree_insert(&root, 3, &cmpf);
    bstree_insert(&root, 7, &cmpf);

    if (root->item != 5 || root->left->item != 3 || root->right->item != 7) {
        printf("Fail\n");
        return 1;
    } else {
        printf("SUCCESS\n");
    }

    // Test 2 unsuccessful insertion
    bstree_insert(&root, 7, &cmpf);  // inserting a duplicate value

    if (root->right->left != NULL) {
        printf("Fail");
        return 1;
    } else {
        printf("SUCCESS");
    }
    return 0;
}