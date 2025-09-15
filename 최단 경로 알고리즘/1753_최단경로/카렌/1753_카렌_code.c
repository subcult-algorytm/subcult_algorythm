#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // INT_MAX 사용

#define MAX_VERTICES 20001 // 정점의 최대 개수 + 1
#define INF INT_MAX       // 무한대를 나타내는 값

// 그래프의 간선을 나타내는 구조체
typedef struct Edge {
    int to;      // 연결된 정점
    int weight;  // 가중치
    struct Edge* next; // 다음 간선을 가리키는 포인터 (인접 리스트용)
} Edge;

// 인접 리스트의 헤드 노드 배열
Edge* adj[MAX_VERTICES];
int dist[MAX_VERTICES]; // 최단 거리를 저장하는 배열
int V, E, K;            // 정점의 수, 간선의 수, 시작 정점

// 우선순위 큐(최소 힙)를 위한 구조체
typedef struct HeapNode {
    int vertex;
    int distance;
} HeapNode;

typedef struct PriorityQueue {
    HeapNode* nodes;
    int capacity;
    int size;
} PriorityQueue;

// 우선순위 큐 생성
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->nodes = (HeapNode*)malloc(sizeof(HeapNode) * (capacity + 1)); // 1-based indexing
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

// 두 HeapNode를 교환하는 함수
void swapHeapNodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// 우선순위 큐에 삽입 (Min Heap)
void pq_push(PriorityQueue* pq, int vertex, int distance) {
    if (pq->size >= pq->capacity) {
        // 필요시 용량 확장 (간단한 구현에서는 생략)
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

// 우선순위 큐에서 최소값 추출 (Min Heap)
HeapNode pq_pop(PriorityQueue* pq) {
    if (pq->size == 0) {
        HeapNode emptyNode = { -1, INF }; // 에러 또는 빈 상태 표시
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

// 그래프에 간선 추가 (인접 리스트)
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

    PriorityQueue* pq = createPriorityQueue(E > V ? E : V); // 힙 크기는 간선 수 또는 정점 수 중 큰 값으로 (넉넉하게)
    pq_push(pq, start_node, 0);

    while (pq->size > 0) {
        HeapNode current = pq_pop(pq);
        int u = current.vertex;
        int d = current.distance;

        if (u == -1) break; // 큐가 비었거나 오류

        // 이미 더 짧은 경로를 찾았다면 무시
        if (d > dist[u]) {
            continue;
        }

        // 현재 정점과 연결된 간선들을 확인
        for (Edge* edge = adj[u]; edge != NULL; edge = edge->next) {
            int v_node = edge->to;
            int weight = edge->weight;

            if (dist[u] != INF && dist[u] + weight < dist[v_node]) {
                dist[v_node] = dist[u] + weight;
                pq_push(pq, v_node, dist[v_node]);
            }
        }
    }
    // 우선순위 큐 메모리 해제
    free(pq->nodes);
    free(pq);
}

int main() 
{
    scanf("%d %d", &V, &E);
    scanf("%d", &K);

    // 인접 리스트 초기화
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

    // 인접 리스트 메모리 해제
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