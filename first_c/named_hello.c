
#include <stdio.h>
#include <string.h>

int main() {
  char str[25];

  printf("Enter your name: ");
  fgets(str, 25, stdin);

  // remove wrap
  str[strcspn(str, "\n")] = 0;

  printf("Hello, %s AI!\n", str);

  return 0;
}
// clang-format -i -style=file named_hello.c to convert google style