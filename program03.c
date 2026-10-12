#include <stdio.h>

#define MAX 5

int stack[MAX];
int top = -1;

void push(void) {
    int item;
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    printf("Enter the element to be pushed: ");
    scanf("%d", &item);
    stack[++top] = item;
}

void pop(void) {
    if (top == -1) printf("Stack Underflow\n");
    else printf("Popped element is %d\n", stack[top--]);
}

void display(void) {
    if (top == -1) {
        printf("Empty Stack\n");
        return;
    }
    printf("The elements of the stack are:\n");
    for (int i = top; i >= 0; i--) printf("stack[%d] = %d\n", i, stack[i]);
}

void palindrome(void) {
    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }
    int is_palindrome = 1;
    for (int i = 0; i <= top / 2; i++) {
        if (stack[i] != stack[top - i]) {
            is_palindrome = 0;
            break;
        }
    }
    if (is_palindrome) printf("Stack contents are Palindrome\n");
    else printf("Stack contents are not palindrome\n");
}

int main(void) {
    int choice;
    while (1) {
        printf("\nSTACK OPERATIONS\n1.Push\n2.Pop\n3.Display\n4.Palindrome\n5.Exit\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) return 0;
        switch (choice) {
            case 1: push(); break;
            case 2: pop(); break;
            case 3: display(); break;
            case 4: palindrome(); break;
            case 5: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
