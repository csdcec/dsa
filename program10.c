#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *ltree;
    struct node *rtree;
} *NODE;

NODE getnode(int value) {
    NODE node = malloc(sizeof(struct node));
    if (node == NULL) exit(1);
    node->value = value;
    node->ltree = NULL;
    node->rtree = NULL;
    return node;
}

NODE create(int item, NODE root) {
    if (root == NULL) return getnode(item);
    NODE current = root;
    NODE parent = NULL;
    while (current != NULL) {
        parent = current;
        if (item == current->value) return root;
        if (item < current->value) current = current->ltree;
        else current = current->rtree;
    }
    if (item < parent->value) parent->ltree = getnode(item);
    else parent->rtree = getnode(item);
    return root;
}

void inorder(NODE root) {
    if (root == NULL) return;
    inorder(root->ltree);
    printf("%d\t", root->value);
    inorder(root->rtree);
}

void preorder(NODE root) {
    if (root == NULL) return;
    printf("%d\t", root->value);
    preorder(root->ltree);
    preorder(root->rtree);
}

void postorder(NODE root) {
    if (root == NULL) return;
    postorder(root->ltree);
    postorder(root->rtree);
    printf("%d\t", root->value);
}

void search(NODE root) {
    int key;
    printf("Enter the element to be searched: ");
    scanf("%d", &key);
    NODE current = root;
    while (current != NULL) {
        if (key == current->value) {
            printf("Found key %d in tree\n", key);
            return;
        }
        if (key < current->value) current = current->ltree;
        else current = current->rtree;
    }
    printf("Key not found\n");
}

void free_tree(NODE root) {
    if (root == NULL) return;
    free_tree(root->ltree);
    free_tree(root->rtree);
    free(root);
}

int main(void) {
    int choice, item, n;
    NODE root = NULL;
    while (1) {
        printf("\n1.Create BST of N integers\n2.BST traversal\n3.Binary search\n4.Exit\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1:
                printf("Enter number of elements: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("Enter the item to be inserted: ");
                    scanf("%d", &item);
                    root = create(item, root);
                }
                break;
            case 2:
                if (root == NULL) printf("Tree is empty\n");
                else {
                    printf("Preorder traversal\n"); preorder(root);
                    printf("\nInorder traversal\n"); inorder(root);
                    printf("\nPostorder traversal\n"); postorder(root);
                    printf("\n");
                }
                break;
            case 3:
                if (root == NULL) printf("Tree is empty\n");
                else search(root);
                break;
            case 4: free_tree(root); return 0;
            default: printf("Invalid choice\n");
        }
    }
    free_tree(root);
    return 0;
}
