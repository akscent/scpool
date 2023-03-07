#ifndef BST_H
#define BST_H

typedef struct s_btree {
    int item;
    struct s_btree *left;
    struct s_btree *right;
} t_btree;

t_btree *bstree_create_node(int item);
void bstree_insert(t_btree *root, int item, int (*cmpf)(int, int));
int cmpf(int a, int b);
void bstree_apply_infix(t_btree *root, void (*applyf)(int));
void bstree_apply_prefix(t_btree *root, void (*applyf)(int));
void bstree_apply_postfix(t_btree *root, void (*applyf)(int));
void print_node(int item);
void bst_print(t_btree *tree);
int s21_strcmp(const char *str1, const char *str2);
void write_to_string(char *str);

#endif
