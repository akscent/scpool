#include "bst.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_btree *bstree_create_node(int item) {
    t_btree *node = (t_btree *)malloc(sizeof(t_btree));
    if (node != NULL) {
        node->item = item;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void bstree_insert(t_btree *root, int item, int (*cmpf)(int, int)) {
    t_btree *node = bstree_create_node(item);

    if (root == NULL) {
        root = node;
        return;
    }

    t_btree *parent = NULL;
    t_btree *current = root;
    while (current != NULL) {
        parent = current;
        if (cmpf(item, current->item) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (cmpf(item, parent->item) < 0) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

int cmpf(int a, int b) {
    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1;
    } else {
        return 0;
    }
}

void bstree_apply_infix(t_btree *root, void (*applyf)(int)) {
    if (root) {
        char node_str[20];
        sprintf(node_str, "%d ", root->item);
        bstree_apply_infix(root->left, applyf);
        applyf(node_str);
        bstree_apply_infix(root->right, applyf);
    }
}

void bstree_apply_prefix(t_btree *root, void (*applyf)(int)) {
    if (root) {
        applyf(root->item);
        bstree_apply_prefix(root->left, applyf);
        bstree_apply_prefix(root->right, applyf);
    }
}

void bstree_apply_postfix(t_btree *root, void (*applyf)(int)) {
    if (root) {
        bstree_apply_postfix(root->left, applyf);
        bstree_apply_postfix(root->right, applyf);
        applyf(root->item);
    }
}

void print_node(int item) { printf("%d ", item); }

void bst_print(t_btree *tree) {
    bstree_apply_infix(tree, print_node);
    printf("\n");
}

int s21_strcmp(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) {
            return -1;
        } else if (str1[i] > str2[i]) {
            return 1;
        }
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 0;
    } else if (str1[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}

void write_to_string(char *str) { strcat(output_str, str); }
