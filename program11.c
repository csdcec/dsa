#include <stdio.h>

#define MAX 20

int adjacency[MAX][MAX];
int visited[MAX];
int n;

void create_graph(void) {
    printf("Enter the number of cities: ");
    scanf("%d", &n);
    if (n < 1 || n >= MAX) {
        n = 0;
        printf("Invalid number of cities\n");
        return;
    }
    printf("Enter graph data in matrix form:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) scanf("%d", &adjacency[i][j]);
    }
}

void bfs(int start) {
    int queue[MAX], front = 0, rear = 0;
    for (int i = 1; i <= n; i++) visited[i] = 0;
    visited[start] = 1;
    queue[rear++] = start;
    while (front < rear) {
        int current = queue[front++];
        for (int i = 1; i <= n; i++) {
            if (adjacency[current][i] != 0 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("Reachable nodes from node %d:\n", start);
    for (int i = 1; i <= n; i++) {
        if (visited[i] && i != start) printf("Node %d\n", i);
    }
}

void dfs_visit(int vertex) {
    visited[vertex] = 1;
    for (int i = 1; i <= n; i++) {
        if (adjacency[vertex][i] != 0 && !visited[i]) dfs_visit(i);
    }
}

void dfs(int start) {
    for (int i = 1; i <= n; i++) visited[i] = 0;
    dfs_visit(start);
    printf("Reachable nodes from node %d:\n", start);
    for (int i = 1; i <= n; i++) {
        if (visited[i] && i != start) printf("Node %d\n", i);
    }
}

int main(void) {
    int choice, start;
    while (1) {
        printf("\n1.Create graph\n2.Display reachable nodes using BFS\n3.Display reachable nodes using DFS\n4.Exit\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) return 0;
        switch (choice) {
            case 1: create_graph(); break;
            case 2:
            case 3:
                if (n == 0) {
                    printf("Create the graph first\n");
                    break;
                }
                printf("Enter the source vertex: ");
                scanf("%d", &start);
                if (start < 1 || start > n) printf("Enter a valid source vertex\n");
                else if (choice == 2) bfs(start);
                else dfs(start);
                break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
