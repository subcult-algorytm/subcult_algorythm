#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // INT_MAX ���

#define MAX_VERTICES 20001 // ������ �ִ� ���� + 1
#define INF INT_MAX       // ���Ѵ븦 ��Ÿ���� ��

// �׷����� ������ ��Ÿ���� ����ü
typedef struct Edge {
    int to;      // ����� ����
    int weight;  // ����ġ
    struct Edge* next; // ���� ������ ����Ű�� ������ (���� ����Ʈ��)
} Edge;

// ���� ����Ʈ�� ��� ��� �迭
Edge* adj[MAX_VERTICES];
int dist[MAX_VERTICES]; // �ִ� �Ÿ��� �����ϴ� �迭
int V, E, K;            // ������ ��, ������ ��, ���� ����

// �켱���� ť(�ּ� ��)�� ���� ����ü
typedef struct HeapNode {
    int vertex;
    int distance;
} HeapNode;

typedef struct PriorityQueue {
    HeapNode* nodes;
    int capacity;
    int size;
} PriorityQueue;

// �켱���� ť ����
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->nodes = (HeapNode*)malloc(sizeof(HeapNode) * (capacity + 1)); // 1-based indexing
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

// �� HeapNode�� ��ȯ�ϴ� �Լ�
void swapHeapNodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// �켱���� ť�� ���� (Min Heap)
void pq_push(PriorityQueue* pq, int vertex, int distance) {
    if (pq->size >= pq->capacity) {
        // �ʿ�� �뷮 Ȯ�� (������ ���������� ����)
        return;
    }
    pq->size++;
    int i = pq->size;
    pq->nodes[i].vertex = vertex;
    pq->nodes[i].distance = distance;

    // Heapify Up
    while (i > 1 && pq->nodes[i].distance < pq->nodes[i / 2].distance) {
        swapHeapNodes(&pq->nodes[i], &pq->nodes[i / 2]);
        i /= 2;
    }
}

// �켱���� ť���� �ּҰ� ���� (Min Heap)
HeapNode pq_pop(PriorityQueue* pq) {
    if (pq->size == 0) {
        HeapNode emptyNode = { -1, INF }; // ���� �Ǵ� �� ���� ǥ��
        return emptyNode;
    }

    HeapNode root = pq->nodes[1];
    pq->nodes[1] = pq->nodes[pq->size];
    pq->size--;

    // Heapify Down
    int i = 1;
    while (1) {
        int smallest = i;
        int left = 2 * i;
        int right = 2 * i + 1;

        if (left <= pq->size && pq->nodes[left].distance < pq->nodes[smallest].distance) {
            smallest = left;
        }
        if (right <= pq->size && pq->nodes[right].distance < pq->nodes[smallest].distance) {
            smallest = right;
        }

        if (smallest != i) {
            swapHeapNodes(&pq->nodes[i], &pq->nodes[smallest]);
            i = smallest;
        }
        else {
            break;
        }
    }
    return root;
}

// �׷����� ���� �߰� (���� ����Ʈ)
void addEdge(int u, int v_node, int w) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->to = v_node;
    newEdge->weight = w;
    newEdge->next = adj[u];
    adj[u] = newEdge;
}

void dijkstra(int start_node) {
    for (int i = 1; i <= V; ++i) {
        dist[i] = INF;
    }
    dist[start_node] = 0;

    PriorityQueue* pq = createPriorityQueue(E > V ? E : V); // �� ũ��� ���� �� �Ǵ� ���� �� �� ū ������ (�˳��ϰ�)
    pq_push(pq, start_node, 0);

    while (pq->size > 0) {
        HeapNode current = pq_pop(pq);
        int u = current.vertex;
        int d = current.distance;

        if (u == -1) break; // ť�� ����ų� ����

        // �̹� �� ª�� ��θ� ã�Ҵٸ� ����
        if (d > dist[u]) {
            continue;
        }

        // ���� ������ ����� �������� Ȯ��
        for (Edge* edge = adj[u]; edge != NULL; edge = edge->next) {
            int v_node = edge->to;
            int weight = edge->weight;

            if (dist[u] != INF && dist[u] + weight < dist[v_node]) {
                dist[v_node] = dist[u] + weight;
                pq_push(pq, v_node, dist[v_node]);
            }
        }
    }
    // �켱���� ť �޸� ����
    free(pq->nodes);
    free(pq);
}

int main() 
{
    scanf("%d %d", &V, &E);
    scanf("%d", &K);

    // ���� ����Ʈ �ʱ�ȭ
    for (int i = 0; i <= V; ++i) {
        adj[i] = NULL;
    }

    for (int i = 0; i < E; ++i) {
        int u_node, v_node, w;
        scanf("%d %d %d", &u_node, &v_node, &w);
        addEdge(u_node, v_node, w);
    }

    dijkstra(K);

    for (int i = 1; i <= V; ++i) {
        if (dist[i] == INF) {
            printf("INF\n");
        }
        else {
            printf("%d\n", dist[i]);
        }
    }

    // ���� ����Ʈ �޸� ����
    for (int i = 1; i <= V; ++i) {
        Edge* current = adj[i];
        while (current != NULL) {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}