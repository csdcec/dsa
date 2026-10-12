#include <stdio.h>
#include <ctype.h>

int stack[100];
int top = -1;

int push(int value) {
    if (top >= 99) return 0;
    stack[++top] = value;
    return 1;
}

int pop(int *value) {
    if (top < 0) return 0;
    *value = stack[top--];
    return 1;
}

int integer_power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) result *= base;
    return result;
}

int main(void) {
    char postfix[100];
    int op1, op2, result;
    printf("Enter the valid postfix expression: ");
    if (scanf("%99s", postfix) != 1) return 1;
    for (int i = 0; postfix[i] != '\0'; i++) {
        char symbol = postfix[i];
        if (isdigit((unsigned char)symbol)) {
            if (!push(symbol - '0')) return 1;
        } else {
            if (!pop(&op2) || !pop(&op1)) {
                printf("Invalid postfix expression\n");
                return 1;
            }
            switch (symbol) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/':
                    if (op2 == 0) { printf("Division by zero\n"); return 1; }
                    result = op1 / op2;
                    break;
                case '%':
                    if (op2 == 0) { printf("Division by zero\n"); return 1; }
                    result = op1 % op2;
                    break;
                case '^': result = integer_power(op1, op2); break;
                default: printf("Invalid operator\n"); return 1;
            }
            if (!push(result)) return 1;
        }
    }
    if (top != 0) {
        printf("Invalid postfix expression\n");
        return 1;
    }
    printf("Result: %d\n", stack[top]);
    return 0;
}
