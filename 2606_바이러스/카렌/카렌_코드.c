#include <stdio.h>

#define MAX_SIZE 1001

int Graph[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE];
int CNT = 0;

void DFS(int v, int Computer_size) {
    visited[v] = 1;
    for (int i = 0; i < Computer_size; i++) {
        if (Graph[v][i] == 1 && visited[i] == 0) {
            CNT++;
            DFS(i, Computer_size);
        }
    }
}

int main() {
    int Computer_size = 0;
    int network_size = 0;

    scanf("%d", &Computer_size);

    for (int i = 0; i < Computer_size; i++) {
        visited[i] = 0;
        for (int j = 0; j < Computer_size; j++) {
            Graph[i][j] = 0;
        }
    }

    scanf("%d", &network_size);

    for (int k = 0; k < network_size; k++) {
        int a, b;
        scanf("%d %d", &a, &b);
        Graph[a-1][b-1] = 1;
        Graph[b-1][a-1] = 1;
    }

    DFS(0, Computer_size); 

    printf("%d\n", CNT);

    return 0;
}
