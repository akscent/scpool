#include <stdlib.h>

#include "documentation_module.h"
#include "print_module.h"

int main() {
#ifdef LOG
    char command[50] = "date +%T";  // command to get current time in HH:MM:SS format
    char current_time[9];
    FILE* pipe = popen(command, "r");  // execute command and open a pipe to read its output
    fgets(current_time, 9, pipe);      // read the output of the command into current_time
    pclose(pipe);                      // close the pipe
    current_time[8] = '\0';            // remove newline character from current_time
    char message[] = "Удача вам сегодня улыбается";
    print_log(print_char, current_time, message);
#endif  // LOG

#ifdef DOC
    const char* document_names[] = {Documents};
    int document_count = sizeof(document_names) / sizeof(document_names[0]);

    int* availability_mask = check_available_documentation_module(validate, document_count, document_names);

    for (int i = 0; i < document_count; i++) {
        printf("[%15s: %s]\n", document_names[i], availability_mask[i] ? "available" : "unavailable");
    }

    free(availability_mask);
#endif  // DOC
    return 0;
}
