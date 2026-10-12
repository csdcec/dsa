#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
    int coef;
    int x;
    int y;
    int z;
    struct node *link;
} *NODE;

NODE getnode(void) {
    NODE node = malloc(sizeof(struct node));
    if (node == NULL) exit(1);
    return node;
}

NODE create_header(void) {
    NODE head = getnode();
    head->coef = -1;
    head->x = -1;
    head->y = -1;
    head->z = -1;
    head->link = head;
    return head;
}

NODE readpoly(void) {
    NODE head = create_header();
    NODE tail = head;
    char choice;
    do {
        NODE term = getnode();
        printf("Enter coefficient and exponents of x, y, z: ");
        if (scanf("%d%d%d%d", &term->coef, &term->x, &term->y, &term->z) != 4) {
            free(term);
            break;
        }
        tail->link = term;
        tail = term;
        tail->link = head;
        printf("Do you want to enter more coefficients (y/n)? ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');
    return head;
}

int compare(NODE a, NODE b) {
    if (a->x != b->x) return a->x > b->x ? 1 : -1;
    if (a->y != b->y) return a->y > b->y ? 1 : -1;
    if (a->z != b->z) return a->z > b->z ? 1 : -1;
    return 0;
}

void attach(int coef, int x, int y, int z, NODE *tail) {
    NODE term = getnode();
    term->coef = coef;
    term->x = x;
    term->y = y;
    term->z = z;
    (*tail)->link = term;
    *tail = term;
}

NODE addpoly(NODE a_head, NODE b_head) {
    NODE a = a_head->link;
    NODE b = b_head->link;
    NODE result = create_header();
    NODE tail = result;
    while (a != a_head && b != b_head) {
        int order = compare(a, b);
        if (order > 0) {
            attach(a->coef, a->x, a->y, a->z, &tail);
            a = a->link;
        } else if (order < 0) {
            attach(b->coef, b->x, b->y, b->z, &tail);
            b = b->link;
        } else {
            int sum = a->coef + b->coef;
            if (sum != 0) attach(sum, a->x, a->y, a->z, &tail);
            a = a->link;
            b = b->link;
        }
    }
    while (a != a_head) {
        attach(a->coef, a->x, a->y, a->z, &tail);
        a = a->link;
    }
    while (b != b_head) {
        attach(b->coef, b->x, b->y, b->z, &tail);
        b = b->link;
    }
    tail->link = result;
    return result;
}

void print_poly(NODE head) {
    if (head == NULL || head->link == head) {
        printf("0");
        return;
    }
    NODE current = head->link;
    while (current != head) {
        printf("%d*x^%d*y^%d*z^%d", current->coef, current->x, current->y, current->z);
        current = current->link;
        if (current != head) printf(" + ");
    }
}

void evaluate(NODE head) {
    int x, y, z;
    double result = 0;
    if (head == NULL) {
        printf("Polynomial is not available\n");
        return;
    }
    printf("Enter the values of x, y, z: ");
    if (scanf("%d%d%d", &x, &y, &z) != 3) return;
    NODE current = head->link;
    while (current != head) {
        result += current->coef * pow(x, current->x) * pow(y, current->y) * pow(z, current->z);
        current = current->link;
    }
    printf("Result: %.2f\n", result);
}

void free_poly(NODE head) {
    if (head == NULL) return;
    NODE current = head->link;
    while (current != head) {
        NODE temp = current;
        current = current->link;
        free(temp);
    }
    free(head);
}

int main(void) {
    int choice;
    NODE a = NULL, b = NULL, c = NULL;
    while (1) {
        printf("\n1.Represent first polynomial A\n2.Represent second polynomial B\n3.Display polynomial A\n4.Display polynomial B\n5.Add A and B\n6.Evaluate sum polynomial\n7.Exit\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1: free_poly(a); a = readpoly(); break;
            case 2: free_poly(b); b = readpoly(); break;
            case 3:
                if (a == NULL) printf("Polynomial A is not available\n");
                else { print_poly(a); printf("\n"); }
                break;
            case 4:
                if (b == NULL) printf("Polynomial B is not available\n");
                else { print_poly(b); printf("\n"); }
                break;
            case 5:
                if (a == NULL || b == NULL) printf("Enter both polynomials first\n");
                else {
                    free_poly(c);
                    c = addpoly(a, b);
                    printf("Sum of two polynomials: ");
                    print_poly(c);
                    printf("\n");
                }
                break;
            case 6: evaluate(c); break;
            case 7: free_poly(a); free_poly(b); free_poly(c); return 0;
            default: printf("Invalid choice\n");
        }
    }
    free_poly(a);
    free_poly(b);
    free_poly(c);
    return 0;
}
