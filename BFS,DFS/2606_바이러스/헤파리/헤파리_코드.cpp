#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

vector<int> adj[1002];
bool vis[1002];

int n, p;
int cnt;

void bfs(int st)
{
	queue<int> q;
	q.push(st);
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		for (auto nxt : adj[cur])
		{
			if (vis[nxt]) continue;
			q.push(nxt);
			vis[nxt] = true;
			cnt++; // 새로운 컴퓨터 방문 - 바이러스 + 1
		}
	}
}

int main(void)
{
	int v, u;
	cin >> n;
	cin >> p;

	while (p--)
	{
		cin >> v >> u;
		adj[v].push_back(u);
		adj[u].push_back(v);
	}

    vis[1] = true;
	bfs(1);

    cout << cnt;

	return 0;
}

