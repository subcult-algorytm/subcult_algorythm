#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

bool visit[301][301];
int dist[301][301];

// 나이트의 이동경로 8개
int dx[8] = { 2, 2, 1, 1, -1, -1, -2, -2 };
int dy[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };

int L, st1, st2, ed1, ed2;

int bfs() 
{
	for (int i = 0; i < L; i++) 
    {
		for (int j = 0; j < L; j++) 
        {
			dist[i][j] = 0;
			visit[i][j] = false;
		}
	}

	visit[st1][st2] = true;
	queue<pair<int, int>> q; 
	q.push({ st1, st2 });
	
	while (!q.empty()) 
    {
		pair<int, int> cur = q.front(); 
        q.pop();

		if (ed1 == cur.first && ed2 == cur.second) 
            return dist[ed1][ed2];

		for (int dir = 0; dir < 8; dir++) 
        {
			int nx = cur.first + dx[dir];
			int ny = cur.second + dy[dir];
			
			if (nx < 0 || ny < 0 || nx >= L || ny >= L) continue;
			if (visit[nx][ny]) continue;
			
			visit[nx][ny] = true;
			dist[nx][ny] = dist[cur.first][cur.second] + 1;
			q.push({ nx, ny });
		}
	}
}

int main(void)
{
	int t;
	cin >> t;
	
	while (t--)
	{
		cin >> L;
		cin >> st1 >> st2; // 초기위치
		cin >> ed1 >> ed2; // 목표
		cout << bfs() << '\n';
	}
}