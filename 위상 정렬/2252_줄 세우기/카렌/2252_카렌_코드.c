#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 32001 // 문제의 최대 학생수가 32000 이므로 + 1
#define MAX_QUEUE_SIZE 32001 // 최악의 경우 모든 학생이 큐에 한번에 들어 갈 수 있으므로 32001로 설정한다.

typedef struct Node {
	int vertex;
	struct Node* next;
}Node;

//----------- 필요한 전역 변수 -----------------------

Node* adjList[MAX_NODES]; // 그래프 인접리스트
int inDegree[MAX_NODES]; // 각 노드의 진입 차수
int result[MAX_NODES]; // 위상 정렬 결과를 저장할 배열
int queue[MAX_QUEUE_SIZE]; // 큐
int front = 0, rear = 0; // 큐의 front,rear 인덱스로 쓰일 변수

//------ 큐 구현 함수들 ---------

void enqueue(int item) { // 큐 에서 원소를 추가해 주는 함수
	queue[rear++] = item;
	// queue[rear] 에 item 을 넣고, rear+1 을 해준다.
}

int dequeue() {// 큐에서 원소를 반환하고 제거해주는 함수이다.
	return queue[front++];
	// queue[front]을 반환하고 front + 1을 해준다.
}

int isQueueEmpty() { // 큐가 비어있는지 확인하는 함수이다.
	return front == rear;
}

void addEdge(int u, int v) { // 인접 리스트에 간선을 추가해 주는 함수이다. u에서 v로 가는 간선을 추가해준다.
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) { // 수정된 부분: = 를 == 로 변경
		// 메모리 할당 실패 처리
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE); // exit() 자체는 프로그램을 종료 시키는 함수이고, EXIT_FAILURE는 프로그램이 성공적으로 실행되지 못했음을 운영체제에게 알림. 이 값의 정수값은 0이 아닌 값
	}
	newNode->vertex = v;
	newNode->next = adjList[u];
	adjList[u] = newNode; // adjList[u]는 u뒤에 있는 원소를 가리키는 배열임.
	inDegree[v]++; // v로 들어오는 간선이므로 v의 진입차수 증가
}

//------메인함수에서 위상 정렬 수행 --------

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);

	// 인접리스트 및 진입 차수 배열 초기화
	for (int i = 1; i <= N; ++i) {
		adjList[i] = NULL;
		inDegree[i] = 0;
	}

	//키 비교 정보 입력 받아 그래프를 구성한다.
	for (int i = 0; i < M; ++i) { // 수정된 부분: ++1 을 ++i 로 변경
		int u, v; // u가 v보다 앞에 서야 한다 (u->v)
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}

	// 진입 차수가 0인 노드들을 큐에 추가
	for (int i = 1; i <= N; ++i) { // 수정된 부분: ++1 을 ++i 로 변경
		if (inDegree[i] == 0) {
			enqueue(i);
		}
	}

	int resultIndex = 0;

	while (!isQueueEmpty()) {
		int u = dequeue(); // dequeue 함수의 반환값인 queue[front]에 있는 데이터를 u에 넣는다.
		result[resultIndex++] = u; // result[resultIndex]에 u(이 코드가 실행된 기준으로 front-1) 값을 넣고 resultIndex + 1을 해준다.

		// 현재 노드u와 연결된 모든 v에 대해 (u에 연결된 v는 하나만 있는것이 아님)
		Node* temp = adjList[u];
		while (temp != NULL) {
			int v = temp->vertex;
			inDegree[v]--;

			// v의 진입 차수가 0이 되면 큐에 추가
			if (inDegree[v] == 0) {
				enqueue(v);
			}
			temp = temp->next;
		}
	}
	// 결과 출력
	for (int i = 0; i < N; ++i) {
		printf("%d ", result[i]);
	}
	printf("\n");

	// 동적 할당된 메모리 해제
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