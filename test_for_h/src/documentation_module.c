#include "documentation_module.h"

#include <stdlib.h>
#include <string.h>
int validate(char *data) {
    int validation_result = !strcmp(data, Available_document);
    return validation_result;
}

int *check_available_documentation_module(int (*validate)(char *), int document_count,
                                          const char **documents) {
    int *availability_mask = (int *)malloc(document_count * sizeof(int));
    for (int i = 0; i < document_count; i++) {
        availability_mask[i] = validate(documents[i]);
    }
    return availability_mask;
}