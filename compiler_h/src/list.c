#include "list.h"

#include <stdlib.h>

struct node* init(const struct door* door) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->door = *door;
    new_node->next = NULL;
    return new_node;
}

struct node* add_door(struct node* elem, const struct door* door) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->door = *door;
    new_node->next = elem->next;
    elem->next = new_node;
    return new_node;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* current = root;
    while (current != NULL) {
        if (current->door.id == door_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct node* remove_door(struct node* elem, struct node* root) {
    if (elem == root) {
        root = elem->next;
        free(elem);
        return root;
    }
    struct node* current = root;
    while (current != NULL && current->next != elem) {
        current = current->next;
    }
    if (current != NULL) {
        current->next = elem->next;
        free(elem);
    }
    return root;
}

void destroy(struct node* root) {
    while (root != NULL) {
        struct node* next = root->next;
        free(root);
        root = next;
    }
}