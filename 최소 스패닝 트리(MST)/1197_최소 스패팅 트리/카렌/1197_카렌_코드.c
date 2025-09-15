// 1. 라이브러리 포함과 자료 구조 정의

#include <stdio.h>
#include <stdlib.h>

struct Edge
{
    int src; // 시작 정점
    int dest; // 도착 정점
    int weight; // 가중치
};

struct Graph
{
    int V; // 정점의 개수
    int E; // 간선의 개수
    struct Edge* edge; // 추후에 간선의 갯수를 사용자에게 입력받을것이므로 포인터 선언
};

struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// 2. Kruskal 알고리즘에 필요한 자료구조와 알고리즘 구현

struct Subset
{
    int parent; // 현재 원소의 부모 원소
    int rank; // 트리의 랭크
};

int find(struct Subset subsets[], int i)
{
    // 자기 자신이 부모가 아닐 경우
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent; // 최종 부모 반환
}

//rank값을 활용해서 Union 연산을 해준다.
void Union(struct Subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // 랭크를 비교한 뒤, 더 작은 트리를 큰 트리에 병합한다
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot; // x의 루트가 y의 루트를 가리키게 한다
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot; // y의 루트가 x의 루트를 가리키게 한다
    else {
        // 랭크가 같다면, 한쪽을 다른 쪽에 붙이고 랭크를 1 증가시킨다
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;

        /*
        subsets[xroot].parent = yroot;
        subsets[yroot].rank ++;
        가 되어도 상관없다
        */

    }
}

//3. 간선 정렬 준비

/*
Kruskal 알고리즘에서 중요한 것은 가중치를 기준으로 오름차순으로 정렬을 하는 것이다.
그렇게 때문에 비교하는 함수를 따로 만들어준다.

참고로 qsort 함수는 c 표준 라이브러리의 qsort 함수를 이용해준다.
*/

int compareEdges(const void* a, const void* b)
{
    //void 포인터를 Edge 포인터로 형변환
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;

    //a1의 가중치가 b1의 가중치보다 작으면 음수, 같으면 0, 크면 양수 반환
    return a1->weight - b1->weight;
}

//4. 본격적인 - Kruskal 알고리즘 구현

/*
Kruskal 알고리즘을 활용하여 최소 스패닝 트리(MST)를 찾아주고 그 총 가중치를 반환해준다.
*/

long long KruskalMST(struct Graph* graph)
{
    int V = graph->V; // 변수 V가 정점의 개수를 받아준다. 여기서 MST에 포함될 간선들을 저장할 배열은 최대 V-1개 이다
    int e = 0; // result 배열의 현재 인덱스 (MST 추가된 간선의 수)
    int i = 0; // 정렬된 간선 배열을 순해하기 위해 사용하는 인덱스이다.
    long long totalWeight = 0;

    /*
    1단계 : 모든 간선을 가중치 오름차순으로 정렬한다.
    graph->edge 배열을, graph->E 개수 만큼, 각 원소의 크기는 sizeof(graph->edge[0]) 만큼
    앞서 만들어준 compareEdges 함수를 사용하여 정렬해준다.
    */

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    /*
    오름차순으로 정렬하기 위한 Subset 배열을 동적으로 할당하고 초기화한다
    각 정점 v는 , 처음에는 자기 자신이 부모고 랭크는 0으로 설정해준다
    */

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    /*
    2단계 : 정렬된 간선들을 순회해주면서 MST를 구성해준다
    MST는 무조건 V-1개의 간선으로 이루어진다 그러므로 e < V-1 조건이 만족 될 때 까지 반복한다
    또한, 모든 간선을 다 확인하기전에 MST가 완성이 될 수 있으므로 i < graph->E 조건도 확인해준다.

    이렇게 하면 하나라도 거짓이 되면 while(0)이 되므로 반복이 멈추게 된다.
    */
    while (e < V - 1 && i < graph->E)
    {
        // 가장 작은 가중치를 가진 다음 간선을 가져온다
        struct Edge next_edge = graph->edge[i++];

        //이 간선의 두 정점이 속한 집합의 대표를 찾아준다.
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        //만약 두 정점의 대표가 다르다면... 즉, 이 간선을 추가해도 사이클이 생기지 않는다면.
        if (x != y)
        {
            e++;
            totalWeight += next_edge.weight;
            Union(subsets, x, y);
        }
    }

    free(subsets);
    return totalWeight;
}

//5. main 함수에서 프로그램 실행

int main()
{
    int V, E;
    scanf("%d %d", &V, &E);

    //V개의 정점과 E개의 간선을 가진 그래프 생성
    struct Graph* graph = createGraph(V, E);

    //E개의 간선 정보를 입력받는다
    for (int i = 0; i < E; ++i)
    {
        //각 간선의 시장 정점,끝 정점, 가중치를 입력 받는다
        /*
        이 문제에서 정점 번호는 1부터 V까지 주어지나, 배열 인덱스는 0부터 v-1까지 사용한다.
        그래서 입력받은 정점번호에서 1을 빼서 저장한다.
        */
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
        graph->edge[i].src--;
        graph->edge[i].dest--;
    }

    //Kruskal 알고리즘을 호출하여 MST의 총 가중치를 계산
    long long mst_weight = KruskalMST(graph);

    printf("%lld\n", mst_weight);

    free(graph->edge);
    free(graph);

    return 0;
}