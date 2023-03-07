#include <stdio.h>

#include "bst.h"

int main() {
    // Test 1: Create a node with value 5
    t_btree *node1 = bstree_create_node(5);
    if (node1 == NULL) {
        printf("FAIL: node\n");
        return 1;
    }
    if (node1->item != 5) {
        printf("FAIL: item\n");
        return 1;
    }
    if (node1->left != NULL || node1->right != NULL) {
        printf("FAIL: side\n");
        return 1;
    }

    // Test 2: Create a node with value 0
    t_btree *node2 = bstree_create_node(0);
    if (node2 == NULL) {
        printf("FAIL: node\n");
        return 1;
    } else {
        printf("SUCCESS\n");
    }
    if (node2->item != 0) {
        printf("FAIL: item\n");
        return 1;
    } else {
        printf("SUCCESS\n");
    }
    if (node2->left != NULL || node2->right != NULL) {
        printf("FAIL: side");
        return 1;
    } else {
        printf("SUCCESS");
    }
    return 0;
}
