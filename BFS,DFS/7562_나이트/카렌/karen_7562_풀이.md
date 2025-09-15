
```
typedef struct {
	int y;
	int x;
} Position;
```

현재 포지션을 저장하기 위한 큐를 선언한다.

```
Position queue[MAX_SIZE * MAX_SIZE + 1];
int moveCount[MAX_SIZE][MAX_SIZE]; 
int knightDy[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };  
int knightDx[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

int front, rear;
```

Position queue : 현재 포지션(혹은 다음포지션)을 저장하기 위한 큐
int moveCount : 정답을 구하기 위해, 현재 몇번 이동했는지 저장하는 변수 
int knightDy[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };  
int knightDx[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
: 방향벡터
int front, rear : 큐에 쓰이는 front와 rear

---

main 함수의 흐름

1. 몇개를 테스트 할것인지 입력 받는다.
2. 시작좌표를 입력받고 목표좌표를 입력 받는다. 
3. 여러번 실험 할 것이므로 BFS 직전에 moveCount를 초기화 시켜준다.
4. BFS 후에 그 결과를 출력시켜준다.
5. 입력받은 테스트 갯수만큼 이를 반복

---
BFS 함수의 흐름 

받는 인수 : 시작 좌표 (int startX , int startY) , 목표좌표 (int target X , int target Y ) , 보드 사이즈 (int boardSize)

1. 시작 좌표를 큐에 넣고 움직이지 않았으므로 moveCount를 0으로 초기화 한다. 
2. 반복문 실행

---

- while (queue[front].y != targetY || queue[front].x != targetX)
-> 현재좌표가 목표좌표가 될때 까지 반복 시킨다.

```
int currY = queue[front].y;
int currX = queue[front].x;
int currentMove = moveCount[currY][currX];
```
currentMove 는 **현재 이동한 횟수를 기록**하는 변수이다.
즉, 현재 좌표가 목표좌표가 될때까지 현재 좌표를 currY와 currX에 넣어주는 작업을 하고,
currentMove에 moveCount 행렬 값을 넣어준다. 

(행렬 값이 0하고 1만 있는 것이 아니고, currentMove값에 의해 값이 채워진다는 것에 유의)

- for (int dir = 0; dir < 8; dir++)

8방향을 다 체크 할때까지 반복한다. 


```
int nextY = currY + knightDy[dir];
int nextX = currX + knightDx[dir]
```
방향벡터를 사용하여 좌표를 바꿔준다. 

-  if (nextY >= 0 && nextY < boardSize && nextX >= 0 && nextX < boardSize)
 
유효한 범위에 있을 경우에만 아래 동작을 반복한다. 


- if (!moveCount[nextY][nextX])

중복 방문을 방지한다. 
만약, next x,y에 대한 값이 0이 아닐 경우 아래 동작을 실행한다.

```
	rear++;
	queue[rear].y = nextY;
	queue[rear].x = nextX;
	moveCount[nextY][nextX] = currentMove + 1;
```

방문 할 노드에 다 방문을 하면 
맨 위 while문이 올바르게 동작을 하기 위해
```
front++;
```
를 실행한다.

- 예시 그림
![[Pasted image 20250407161350.png]]

0,0에서 출발하여 횟수가 두번 필요한 곳은 1이 아니라 2로 표기 됨에 유의. 