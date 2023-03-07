#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct Node {
    char data;
    struct Node* next;
} Node;
typedef struct Stack {
    Node* top;
} Stack;
Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}
int isDigit(char c) { // функция для проверки, является ли символ цифрой
    return (c >= "0" && c <= "9");
}
void free_stack(Stack* s) {
    while (s->top != NULL) {
        Node* tmp = s->top;
        s->top = s->top->next;
        free(tmp);
    }
    free(s);
}
int isalpha(int c) {
    return (c >= "A" && c <= "Z") || (c >= "a" && c <= "z");
}
int is_empty(Stack* stack) {
    return stack->top == NULL;
}
void push(Stack* stack, char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = stack->top;
    stack->top = node;
}
char peek(Stack* stack) {
    if (is_empty(stack)) {
        printf("Error: Stack is empty.\n");
        exit(1);
    }
    return stack->top->data;
}
char pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("Error: Stack is empty.\n");
        exit(1);
    }
    char data = stack->top->data;
    Node* node = stack->top;
    stack->top = stack->top->next;
    free(node);
    return data;
}
int is_operator(char c) {
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "s" || c == "c" || c == "t" || c == "g" || c == "q" || c == "l");
}
int is_operand(char* str) {
    int len = strlen(str);
    int has_decimal = 0;
    for (int i = 0; i < len; i++) {
        if (i == 0 && (str[i] == "+" || str[i] == "-")) {
            // the first character can be a sign (+ or -)
            continue;
        }
        if (str[i] == ".") {
            if (has_decimal) {
                // there can be only one decimal point in a number
                return 0;
            }
            has_decimal = 1;
        } else if (!isDigit(str[i])) {
            // if any character is not a digit or a decimal point, it"s not a number
            return 0;
        }
    }
    return 1;
}
int precedence(char op) {
    if (op == "+" || op == "-") {
        return 1;
    } else if (op == "*" || op == "/") {
        return 2;
    } else if (op == "s" || op == "c" || op == "t" || op == "g" || op == "q" || op == "l") {
        return 3;
    } else {
        return 0;
    }
}
void infix_to_prefix(char *infix, char *prefix) {
    int i, j, len;
    char c, temp;
    Stack *s = create_stack(strlen(infix));
    len = strlen(infix);
    // for (i = 0, j = len - 1; i <= j; i++, j--) {
    //     temp = infix[i];
    //     infix[i] = infix[j];
    //     infix[j] = temp;
    // }
    i = 0;
    j = 0;
    while (infix[i] != "\0") {
        c = infix[i];
        i++;
        if (c == ' ') {
            i++;
            continue;
        }
        if (!is_operator(c)) {
            int has_decimal = 0;
            int num_digits = 0;
            while (isDigit(c) || c == ".") {
                prefix[j] = c;
                j++;
                c = infix[i];
                i++;
                num_digits++;
                if (c == ".") {
                    if (has_decimal) {
                        return;
                    }
                    has_decimal = 1;
                } else if (!isDigit(c)) {
                    break;
                }
            }
            if (num_digits > 0) {
                // add a space after the operand
                prefix[j] = ' ';
                j++;
                i--;
            }
        } else if (c == ")") {
            push(s, c);
        } else if (c == "(") {
            while (peek(s) != ")") {
                prefix[j] = pop(s);
                j++;
                prefix[j] = ' '; // add a space after the operator
                j++;
            }
            pop(s);
        } else {
            while (!is_empty(s) && precedence(peek(s)) > precedence(c)) {
                prefix[j] = pop(s);
                j++;
                prefix[j] = " "; // add a space after the operator
                j++;
            }
            if (isalpha(c)) {
                if (c == "c") {
                // Если косинус, заносим в стек символ "cos"
                    push(s, "c");
                } else if (c == "s" && infix[i + 1] == "i") {
                // Если котангенс, заносим в стек символ "ctg"
                    push(s, "s");
                } else if (c == "c" && infix[i + 1] == "t") {
                // Если котангенс, заносим в стек символ "ctg"
                    push(s, "t");
                } else if (c == "s" && infix[i + 1] == "q") {
                // Если корень, заносим в стек символ "sqrt"
                    push(s, "q");
                } else if (c == "l") {
                // Если натуральный логарифм, заносим в стек символ "l"
                    push(s, "l");
                } else {
                // Иначе, заносим в стек оператор
                    printf("napisal govno");
                    exit(1);
                } // push the current operator onto the stack
            } else
                push(s, c);
            if ((c == "s" && infix[i + 1] == "i") || c == "c" || c == "t" || c == "g")
                // Пропускаем два символа если это sin cos tan ctg
                i += 2;
            else if (c == "s" && infix[i + 1] == "q")
                // Пропускаем три символа если это sqrt
                i += 3;
            else if (c == "l")
                // Пропускаем один символ если это ln
                i += 1;
        }
    }
    while (!is_empty(s)) {
        prefix[j] = pop(s);
        j++;
        prefix[j] = ' '; // add a space after the operator
        j++;
    }
    prefix[j] = "\0"; // add null character at the end of prefix expression
    len = strlen(prefix);
    for (i = 0, j = len - 1; i <= j; i++, j--) {
        temp = prefix[i];
        prefix[i] = prefix[j];
        prefix[j] = temp;
    }
    free_stack(s);
}
double evaluate_prefix(char* prefix) {
    int i, j, len;
    double operand1, operand2, result;
    char c;
    Stack* s = create_stack(strlen(prefix));
    len = strlen(prefix);
    for (i = 0, j = len - 1; i <= j; i++, j--) {
        char temp = prefix[i];
        prefix[i] = prefix[j];
        prefix[j] = temp;
    }
    for (i = len - 1; i >= 0; i--) {
        push(s, prefix[i]);
    }
    while (!is_empty(s)) {
        c = pop(s);
        if (is_operator(c)) {
            if (is_empty(s)) {
                // Error: not enough operands
                result = NAN;
                break;
            }
            operand1 = pop(s);
            if (is_empty(s)) {
                // Error: not enough operands
                result = NAN;
                break;
            }
            operand2 = pop(s);
            switch(c) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                case '^':
                    result = pow(operand1, operand2);
                    break;
                case 's':
                    result = sin(operand2);
                    break;
                case 'c':
                    result = cos(operand2);
                    break;
                case 't':
                    result = tan(operand2);
                    break;
                case 'q':
                    result = sqrt(operand2);
                    break;
                case 'l':
                    result = log(operand2);
                    break;
                case 'g':
                    result = cos(operand2) / sin(operand2);
                    break;
                default:
                    // Error: unknown operator
                    result = NAN;
                    break;
            }
            if (!isnan(result)) {
                push(s, result);
            } else {
                // Propagate error
                break;
            }
        } else if (isDigit(c)) {
            double value = c - '0';
            push(s, value);
        } else {
            // Error: unknown token
            result = NAN;
            break;
        }
    }
    result = pop(s);
    free_stack(s);
    return result;
}
int main() {
    char infix[100], prefix[100];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    infix_to_prefix(infix, prefix);
    printf("The prefix expression is: %s\n", prefix);
    double result = evaluate_prefix(prefix);
    printf("Result: %.2f\n", result);
    return 0;
}