#include <stdio.h>
#include <ctype.h>

char infix[100], postfix[100], stack[100];
int top = -1;

int priority(char symbol) {
    switch (symbol) {
        case '+':
        case '-': return 1;
        case '*':
        case '/':
        case '%': return 2;
        case '^': return 3;
        default: return 0;
    }
}

void push(char item) {
    stack[++top] = item;
}

char pop(void) {
    return stack[top--];
}

void infix_to_postfix(void) {
    int i = 0, j = 0;
    char symbol;
    top = -1;
    for (i = 0; infix[i] != '\0'; i++) {
        symbol = infix[i];
        if (isalnum((unsigned char)symbol)) {
            postfix[j++] = symbol;
        } else if (symbol == '(') {
            push(symbol);
        } else if (symbol == ')') {
            while (top >= 0 && stack[top] != '(') postfix[j++] = pop();
            if (top >= 0 && stack[top] == '(') pop();
        } else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '%' || symbol == '^') {
            while (top >= 0 && stack[top] != '(' &&
                   (priority(stack[top]) > priority(symbol) ||
                    (priority(stack[top]) == priority(symbol) && symbol != '^'))) {
                postfix[j++] = pop();
            }
            push(symbol);
        }
    }
    while (top >= 0) {
        if (stack[top] == '(') pop();
        else postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

int main(void) {
    printf("Enter the valid infix expression: ");
    if (scanf("%99s", infix) != 1) return 1;
    infix_to_postfix();
    printf("Infix expression: %s\n", infix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}
