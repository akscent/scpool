#include "list.h"

#include <stdio.h>

#define SUCCESS 0
#define FAIL 1

int test_add_door() {
    struct door doors[3] = {{0, 0}, {1, 0}, {2, 0}};
    struct node* root = init(&doors[0]);
    add_door(root, &doors[1]);
    add_door(root->next, &doors[2]);
    if (root->door.id != 0 || root->next->door.id != 1 || root->next->next->door.id != 2) {
        return FAIL;
    }
    destroy(root);
    return SUCCESS;
}

int test_remove_door() {
    struct door door1 = {0, 0};
    struct door door2 = {1, 0};
    struct door door3 = {2, 0};
    struct node* root = init(&door1);
    add_door(root, &door2);
    add_door(root, &door3);
    struct node* elem = find_door(1, root);
    remove_door(elem, root);
    if (root->door.id != 0 || root->next->door.id != 2 || root->next->next != NULL) {
        destroy(root);
        return FAIL;
    }
    root = remove_door(root, root);
    root = remove_door(root, root);
    if (root != NULL) {
        destroy(root);
        return FAIL;
    }
    destroy(root);
    return SUCCESS;
}

int main() {
    int add_result = test_add_door();
    if (add_result == SUCCESS) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
    int remove_result = test_remove_door();
    if (remove_result == SUCCESS) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    // if (add_result == SUCCESS && remove_result == SUCCESS) {
    //     printf("ALL SUCCESS");
    // } else {
    //     printf("Something FAIL");
    // }

    return 0;
}
