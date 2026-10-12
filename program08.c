#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char ssn[15];
    char name[30];
    char dept[25];
    char desig[25];
    unsigned long long phno;
    float sal;
    struct node *prev;
    struct node *next;
} *NODE;

NODE FIRST = NULL;
NODE END = NULL;

NODE getnode(void) {
    NODE node = malloc(sizeof(struct node));
    if (node == NULL) exit(1);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

NODE read_employee(void) {
    NODE node = getnode();
    printf("Enter SSN: ");
    scanf("%14s", node->ssn);
    printf("Enter name: ");
    scanf("%29s", node->name);
    printf("Enter department: ");
    scanf("%24s", node->dept);
    printf("Enter designation: ");
    scanf("%24s", node->desig);
    printf("Enter phone number: ");
    scanf("%llu", &node->phno);
    printf("Enter salary: ");
    scanf("%f", &node->sal);
    return node;
}

void create_dll(void) {
    int n;
    printf("Enter the number of employees: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        NODE node = read_employee();
        if (FIRST == NULL) FIRST = END = node;
        else {
            END->next = node;
            node->prev = END;
            END = node;
        }
    }
}

void display_count(void) {
    int count = 0;
    NODE current = FIRST;
    if (current == NULL) {
        printf("Employee list is empty and count is 0\n");
        return;
    }
    printf("SSN\tNAME\tDEPARTMENT\tDESIGNATION\tPHONE\tSALARY\n");
    while (current != NULL) {
        printf("%s\t%s\t%s\t%s\t%llu\t%.2f\n", current->ssn, current->name, current->dept, current->desig, current->phno, current->sal);
        count++;
        current = current->next;
    }
    printf("Employee count is %d\n", count);
}

void insert_front(void) {
    NODE node = read_employee();
    if (FIRST == NULL) FIRST = END = node;
    else {
        node->next = FIRST;
        FIRST->prev = node;
        FIRST = node;
    }
}

void insert_end(void) {
    NODE node = read_employee();
    if (END == NULL) FIRST = END = node;
    else {
        END->next = node;
        node->prev = END;
        END = node;
    }
}

void delete_front(void) {
    if (FIRST == NULL) {
        printf("List is empty\n");
        return;
    }
    NODE temp = FIRST;
    printf("Deleted element is %s\n", temp->ssn);
    FIRST = FIRST->next;
    if (FIRST == NULL) END = NULL;
    else FIRST->prev = NULL;
    free(temp);
}

void delete_end(void) {
    if (END == NULL) {
        printf("List is empty\n");
        return;
    }
    NODE temp = END;
    printf("Deleted element is %s\n", temp->ssn);
    END = END->prev;
    if (END == NULL) FIRST = NULL;
    else END->next = NULL;
    free(temp);
}

void display_reverse(void) {
    if (END == NULL) {
        printf("List is empty\n");
        return;
    }
    NODE current = END;
    while (current != NULL) {
        printf("%s\t%s\t%.2f\n", current->ssn, current->name, current->sal);
        current = current->prev;
    }
}

void free_list(void) {
    while (FIRST != NULL) {
        NODE temp = FIRST;
        FIRST = FIRST->next;
        free(temp);
    }
    END = NULL;
}

int main(void) {
    int choice;
    while (1) {
        printf("\n1.Create DLL\n2.Display DLL and count\n3.Insert at front\n4.Insert at end\n5.Delete at front\n6.Delete at end\n7.Display in reverse\n8.Exit\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1: create_dll(); break;
            case 2: display_count(); break;
            case 3: insert_front(); break;
            case 4: insert_end(); break;
            case 5: delete_front(); break;
            case 6: delete_end(); break;
            case 7: display_reverse(); break;
            case 8: free_list(); return 0;
            default: printf("Invalid choice\n");
        }
    }
    free_list();
    return 0;
}
