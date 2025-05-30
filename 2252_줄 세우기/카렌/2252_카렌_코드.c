#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 32001 // ������ �ִ� �л����� 32000 �̹Ƿ� + 1
#define MAX_QUEUE_SIZE 32001 // �־��� ��� ��� �л��� ť�� �ѹ��� ��� �� �� �����Ƿ� 32001�� �����Ѵ�.

typedef struct Node {
	int vertex;
	struct Node* next;
}Node;

//----------- �ʿ��� ���� ���� -----------------------

Node* adjList[MAX_NODES]; // �׷��� ��������Ʈ
int inDegree[MAX_NODES]; // �� ����� ���� ����
int result[MAX_NODES]; // ���� ���� ����� ������ �迭
int queue[MAX_QUEUE_SIZE]; // ť
int front = 0, rear = 0; // ť�� front,rear �ε����� ���� ����

//------ ť ���� �Լ��� ---------

void enqueue(int item) { // ť ���� ���Ҹ� �߰��� �ִ� �Լ�
	queue[rear++] = item;
	// queue[rear] �� item �� �ְ�, rear+1 �� ���ش�.
}

int dequeue() {// ť���� ���Ҹ� ��ȯ�ϰ� �������ִ� �Լ��̴�.
	return queue[front++];
	// queue[front]�� ��ȯ�ϰ� front + 1�� ���ش�.
}

int isQueueEmpty() { // ť�� ����ִ��� Ȯ���ϴ� �Լ��̴�.
	return front == rear;
}

void addEdge(int u, int v) { // ���� ����Ʈ�� ������ �߰��� �ִ� �Լ��̴�. u���� v�� ���� ������ �߰����ش�.
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) { // ������ �κ�: = �� == �� ����
		// �޸� �Ҵ� ���� ó��
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE); // exit() ��ü�� ���α׷��� ���� ��Ű�� �Լ��̰�, EXIT_FAILURE�� ���α׷��� ���������� ������� �������� �ü������ �˸�. �� ���� �������� 0�� �ƴ� ��
	}
	newNode->vertex = v;
	newNode->next = adjList[u];
	adjList[u] = newNode; // adjList[u]�� u�ڿ� �ִ� ���Ҹ� ����Ű�� �迭��.
	inDegree[v]++; // v�� ������ �����̹Ƿ� v�� �������� ����
}

//------�����Լ����� ���� ���� ���� --------

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);

	// ��������Ʈ �� ���� ���� �迭 �ʱ�ȭ
	for (int i = 1; i <= N; ++i) {
		adjList[i] = NULL;
		inDegree[i] = 0;
	}

	//Ű �� ���� �Է� �޾� �׷����� �����Ѵ�.
	for (int i = 0; i < M; ++i) { // ������ �κ�: ++1 �� ++i �� ����
		int u, v; // u�� v���� �տ� ���� �Ѵ� (u->v)
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}

	// ���� ������ 0�� ������ ť�� �߰�
	for (int i = 1; i <= N; ++i) { // ������ �κ�: ++1 �� ++i �� ����
		if (inDegree[i] == 0) {
			enqueue(i);
		}
	}

	int resultIndex = 0;

	while (!isQueueEmpty()) {
		int u = dequeue(); // dequeue �Լ��� ��ȯ���� queue[front]�� �ִ� �����͸� u�� �ִ´�.
		result[resultIndex++] = u; // result[resultIndex]�� u(�� �ڵ尡 ����� �������� front-1) ���� �ְ� resultIndex + 1�� ���ش�.

		// ���� ���u�� ����� ��� v�� ���� (u�� ����� v�� �ϳ��� �ִ°��� �ƴ�)
		Node* temp = adjList[u];
		while (temp != NULL) {
			int v = temp->vertex;
			inDegree[v]--;

			// v�� ���� ������ 0�� �Ǹ� ť�� �߰�
			if (inDegree[v] == 0) {
				enqueue(v);
			}
			temp = temp->next;
		}
	}
	// ��� ���
	for (int i = 0; i < N; ++i) {
		printf("%d ", result[i]);
	}
	printf("\n");

	// ���� �Ҵ�� �޸� ����
	for (int i = 1; i <= N; ++i) {
		Node* current = adjList[i];
		while (current != NULL) {
			Node* nextNode = current->next;
			free(current);
			current = nextNode;
		}
	}
	return 0;
}