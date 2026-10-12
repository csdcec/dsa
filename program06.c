#include <stdio.h>

#define MAX 6

char q[MAX];
int front = -1, rear = -1;

void insert(void) {
    char item;
    if ((front == 0 && rear == MAX - 1) || (front == rear + 1)) {
        printf("Circular Queue Overflow\n");
        return;
    }
    if (front == -1) front = rear = 0;
    else rear = (rear + 1) % MAX;
    printf("Enter the character to be inserted: ");
    scanf(" %c", &item);
    q[rear] = item;
}

void delete_item(void) {
    if (front == -1) {
        printf("Circular Queue Underflow\n");
        return;
    }
    printf("Deleted character is: %c\n", q[front]);
    if (front == rear) front = rear = -1;
    else front = (front + 1) % MAX;
}

void display(void) {
    if (front == -1) {
        printf("Circular Queue is Empty\n");
        return;
    }
    printf("Contents of Queue are:\n");
    int i = front;
    while (1) {
        printf("%c\t", q[i]);
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main(void) {
    int choice;
    while (1) {
        printf("\nCIRCULAR QUEUE OPERATIONS\n1.Insert\n2.Delete\n3.Display\n4.Exit\nEnter the choice: ");
        if (scanf("%d", &choice) != 1) return 0;
        switch (choice) {
            case 1: insert(); break;
            case 2: delete_item(); break;
            case 3: display(); break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
