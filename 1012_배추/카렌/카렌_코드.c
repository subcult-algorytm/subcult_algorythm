#include <stdio.h>
#include <string.h>

int field[50][50];
int visited[50][50];
int M, N; // M:가로 , N: 세로

void dfs(int r, int c) {
	if (r < 0 || r >= N || c < 0 || c >= M) {
		return;
	}
	if (field[r][c] == 0 || visited[r][c] == 1) {
		return;
	}

	visited[r][c] = 1;

	dfs(r + 1, c); // 하
	dfs(r - 1, c); // 상
	dfs(r, c + 1); // 우
	dfs(r, c - 1); // 좌 
}

int main() {
	int T;
	scanf("%d", &T);

	while (T--) {
		int K; // 배추개수
		int count = 0; // 필요한 지렁이 수 

		scanf("%d %d %d", &M, &N, &K);

		memset(field, 0, sizeof(field));

		memset(visited, 0, sizeof(visited));

		for (int i = 0; i < K; i++) {
			int X, Y;
			scanf("%d %d", &X, &Y);
			field[Y][X] = 1;
		}

		// 배추밭 전체 탐색
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (field[r][c] == 1 && visited[r][c] == 0) {
					dfs(r, c);
					count++;
				}
			}
		}
		printf("%d\n", count);
	}
	return 0;
}