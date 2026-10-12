#include <stdio.h>

#define MAX 10

void display(const int table[MAX]) {
    printf("Hash table\nAddress\tKey\n");
    for (int i = 0; i < MAX; i++) printf("%d\t%d\n", i, table[i]);
}

void linear_prob(int table[MAX]) {
    int key;
    printf("Enter 4-digit key: ");
    if (scanf("%d", &key) != 1) return;
    int address = key % MAX;
    for (int i = 0; i < MAX; i++) {
        int index = (address + i) % MAX;
        if (table[index] == key) {
            printf("Key already exists at address %d\n", index);
            return;
        }
        if (table[index] == -1) {
            table[index] = key;
            printf("Key inserted at address %d\n", index);
            return;
        }
    }
    printf("Hash table is full\n");
}

int main(void) {
    int table[MAX];
    int choice;
    for (int i = 0; i < MAX; i++) table[i] = -1;
    while (1) {
        printf("\nCollision handling by Linear Probing\n1.Insert into hash table\n2.Display hash table\n3.Exit\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) return 0;
        switch (choice) {
            case 1: linear_prob(table); break;
            case 2: display(table); break;
            case 3: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
