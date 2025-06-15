// 1. ���̺귯�� ���԰� �ڷ� ���� ����

#include <stdio.h>
#include <stdlib.h>

struct Edge
{
    int src; // ���� ����
    int dest; // ���� ����
    int weight; // ����ġ
};

struct Graph
{
    int V; // ������ ����
    int E; // ������ ����
    struct Edge* edge; // ���Ŀ� ������ ������ ����ڿ��� �Է¹������̹Ƿ� ������ ����
};

struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// 2. Kruskal �˰��� �ʿ��� �ڷᱸ���� �˰��� ����

struct Subset
{
    int parent; // ���� ������ �θ� ����
    int rank; // Ʈ���� ��ũ
};

int find(struct Subset subsets[], int i)
{
    // �ڱ� �ڽ��� �θ� �ƴ� ���
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent; // ���� �θ� ��ȯ
}

//rank���� Ȱ���ؼ� Union ������ ���ش�.
void Union(struct Subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // ��ũ�� ���� ��, �� ���� Ʈ���� ū Ʈ���� �����Ѵ�
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot; // x�� ��Ʈ�� y�� ��Ʈ�� ����Ű�� �Ѵ�
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot; // y�� ��Ʈ�� x�� ��Ʈ�� ����Ű�� �Ѵ�
    else {
        // ��ũ�� ���ٸ�, ������ �ٸ� �ʿ� ���̰� ��ũ�� 1 ������Ų��
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;

        /*
        subsets[xroot].parent = yroot;
        subsets[yroot].rank ++;
        �� �Ǿ �������
        */

    }
}

//3. ���� ���� �غ�

/*
Kruskal �˰��򿡼� �߿��� ���� ����ġ�� �������� ������������ ������ �ϴ� ���̴�.
�׷��� ������ ���ϴ� �Լ��� ���� ������ش�.

����� qsort �Լ��� c ǥ�� ���̺귯���� qsort �Լ��� �̿����ش�.
*/

int compareEdges(const void* a, const void* b)
{
    //void �����͸� Edge �����ͷ� ����ȯ
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;

    //a1�� ����ġ�� b1�� ����ġ���� ������ ����, ������ 0, ũ�� ��� ��ȯ
    return a1->weight - b1->weight;
}

//4. �������� - Kruskal �˰��� ����

/*
Kruskal �˰����� Ȱ���Ͽ� �ּ� ���д� Ʈ��(MST)�� ã���ְ� �� �� ����ġ�� ��ȯ���ش�.
*/

long long KruskalMST(struct Graph* graph)
{
    int V = graph->V; // ���� V�� ������ ������ �޾��ش�. ���⼭ MST�� ���Ե� �������� ������ �迭�� �ִ� V-1�� �̴�
    int e = 0; // result �迭�� ���� �ε��� (MST �߰��� ������ ��)
    int i = 0; // ���ĵ� ���� �迭�� �����ϱ� ���� ����ϴ� �ε����̴�.
    long long totalWeight = 0;

    /*
    1�ܰ� : ��� ������ ����ġ ������������ �����Ѵ�.
    graph->edge �迭��, graph->E ���� ��ŭ, �� ������ ũ��� sizeof(graph->edge[0]) ��ŭ
    �ռ� ������� compareEdges �Լ��� ����Ͽ� �������ش�.
    */

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    /*
    ������������ �����ϱ� ���� Subset �迭�� �������� �Ҵ��ϰ� �ʱ�ȭ�Ѵ�
    �� ���� v�� , ó������ �ڱ� �ڽ��� �θ�� ��ũ�� 0���� �������ش�
    */

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    /*
    2�ܰ� : ���ĵ� �������� ��ȸ���ָ鼭 MST�� �������ش�
    MST�� ������ V-1���� �������� �̷������ �׷��Ƿ� e < V-1 ������ ���� �� �� ���� �ݺ��Ѵ�
    ����, ��� ������ �� Ȯ���ϱ����� MST�� �ϼ��� �� �� �����Ƿ� i < graph->E ���ǵ� Ȯ�����ش�.

    �̷��� �ϸ� �ϳ��� ������ �Ǹ� while(0)�� �ǹǷ� �ݺ��� ���߰� �ȴ�.
    */
    while (e < V - 1 && i < graph->E)
    {
        // ���� ���� ����ġ�� ���� ���� ������ �����´�
        struct Edge next_edge = graph->edge[i++];

        //�� ������ �� ������ ���� ������ ��ǥ�� ã���ش�.
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        //���� �� ������ ��ǥ�� �ٸ��ٸ�... ��, �� ������ �߰��ص� ����Ŭ�� ������ �ʴ´ٸ�.
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

//5. main �Լ����� ���α׷� ����

int main()
{
    int V, E;
    scanf("%d %d", &V, &E);

    //V���� ������ E���� ������ ���� �׷��� ����
    struct Graph* graph = createGraph(V, E);

    //E���� ���� ������ �Է¹޴´�
    for (int i = 0; i < E; ++i)
    {
        //�� ������ ���� ����,�� ����, ����ġ�� �Է� �޴´�
        /*
        �� �������� ���� ��ȣ�� 1���� V���� �־�����, �迭 �ε����� 0���� v-1���� ����Ѵ�.
        �׷��� �Է¹��� ������ȣ���� 1�� ���� �����Ѵ�.
        */
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
        graph->edge[i].src--;
        graph->edge[i].dest--;
    }

    //Kruskal �˰����� ȣ���Ͽ� MST�� �� ����ġ�� ���
    long long mst_weight = KruskalMST(graph);

    printf("%lld\n", mst_weight);

    free(graph->edge);
    free(graph);

    return 0;
}