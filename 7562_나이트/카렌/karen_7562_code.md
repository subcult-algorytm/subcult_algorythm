```
#include <stdio.h>
#define MAX_SIZE 300

typedef struct {
	int y;
	int x;
} Position;

Position queue[MAX_SIZE * MAX_SIZE + 1];
int moveCount[MAX_SIZE][MAX_SIZE]; 
int knightDy[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };  
int knightDx[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

int front, rear;

void BFS(int startX, int startY, int targetX, int targetY, int boardSize);

int main() {
	int testCaseCount, boardSize;
	int startX, startY, targetX, targetY;

	scanf("%d", &testCaseCount);

	for (int i = 0; i < testCaseCount; i++) {
		scanf("%d", &boardSize);
		scanf("%d %d", &startX, &startY);
		scanf("%d %d", &targetX, &targetY);

		for (int y = 0; y < boardSize; y++)
			for (int x = 0; x < boardSize; x++)
				moveCount[y][x] = 0;

		BFS(startX, startY, targetX, targetY, boardSize);
		printf("%d\n", moveCount[targetY][targetX]);
	}

	return 0;
}

void BFS(int startX, int startY, int targetX, int targetY, int boardSize) {
	front = 0;
	rear = 0;
	queue[rear].y = startY;
	queue[rear].x = startX;
	moveCount[startY][startX] = 0;

	while (queue[front].y != targetY || queue[front].x != targetX) {
		int currY = queue[front].y;
		int currX = queue[front].x;
		int currentMove = moveCount[currY][currX];

		for (int dir = 0; dir < 8; dir++) {
			int nextY = currY + knightDy[dir];
			int nextX = currX + knightDx[dir];
			if (nextY >= 0 && nextY < boardSize && nextX >= 0 && nextX < boardSize) {
				if (!moveCount[nextY][nextX]) {
					rear++;
					queue[rear].y = nextY;
					queue[rear].x = nextX;
					moveCount[nextY][nextX] = currentMove + 1;
				}
			}
		}
		front++;
	}
}

```