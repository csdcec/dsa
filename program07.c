#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char usn[20];
    char name[30];
    char branch[10];
    unsigned long long phno;
    int sem;
    struct node *link;
} *NODE;

NODE FIRST = NULL;

NODE getnode(void) {
    NODE node = malloc(sizeof(struct node));
    if (node == NULL) exit(1);
    node->link = NULL;
    return node;
}

NODE read_student(void) {
    NODE node = getnode();
    printf("Enter USN: ");
    scanf("%19s", node->usn);
    printf("Enter name: ");
    scanf("%29s", node->name);
    printf("Enter branch: ");
    scanf("%9s", node->branch);
    printf("Enter phone number: ");
    scanf("%llu", &node->phno);
    printf("Enter semester: ");
    scanf("%d", &node->sem);
    return node;
}

void create_sll(void) {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        NODE node = read_student();
        node->link = FIRST;
        FIRST = node;
    }
}

void display_count(void) {
    int count = 0;
    NODE current = FIRST;
    if (current == NULL) {
        printf("Student list is empty and count is 0\n");
        return;
    }
    printf("USN\tNAME\tBRANCH\tPHONE\tSEMESTER\n");
    while (current != NULL) {
        printf("%s\t%s\t%s\t%llu\t%d\n", current->usn, current->name, current->branch, current->phno, current->sem);
        count++;
        current = current->link;
    }
    printf("Student count is %d\n", count);
}

void insert_front(void) {
    NODE node = read_student();
    node->link = FIRST;
    FIRST = node;
}

void insert_end(void) {
    NODE node = read_student();
    if (FIRST == NULL) {
        FIRST = node;
        return;
    }
    NODE current = FIRST;
    while (current->link != NULL) current = current->link;
    current->link = node;
}

void delete_front(void) {
    if (FIRST == NULL) {
        printf("List is empty\n");
        return;
    }
    NODE temp = FIRST;
    printf("Deleted element is %s\n", temp->usn);
    FIRST = FIRST->link;
    free(temp);
}

void delete_end(void) {
    if (FIRST == NULL) {
        printf("List is empty\n");
        return;
    }
    if (FIRST->link == NULL) {
        printf("Deleted element is %s\n", FIRST->usn);
        free(FIRST);
        FIRST = NULL;
        return;
    }
    NODE previous = NULL, current = FIRST;
    while (current->link != NULL) {
        previous = current;
        current = current->link;
    }
    printf("Deleted element is %s\n", current->usn);
    previous->link = NULL;
    free(current);
}

void free_list(void) {
    while (FIRST != NULL) {
        NODE temp = FIRST;
        FIRST = FIRST->link;
        free(temp);
    }
}

int main(void) {
    int choice;
    while (1) {
        printf("\n1.Create SLL\n2.Display SLL and count\n3.Insert front\n4.Insert end\n5.Delete front\n6.Delete end\n7.Exit\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1: create_sll(); break;
            case 2: display_count(); break;
            case 3: insert_front(); break;
            case 4: insert_end(); break;
            case 5: delete_front(); break;
            case 6: delete_end(); break;
            case 7: free_list(); return 0;
            default: printf("Invalid choice\n");
        }
    }
    free_list();
    return 0;
}
