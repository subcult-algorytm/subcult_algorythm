#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int degree[100002];
vector<int> adj[100002]; 

queue<int> q; // 선형 자료구조라면 아무거나 사용 가능
vector<int> answer;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++)
    {
        // u -> v
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        degree[v]++; 
    }

    for (int i = 1; i <= n; i++)
        if (degree[i] == 0) q.push(i);

    // bfs 스타일 (khan)
    while (!q.empty())
    {
        int cur = q.front(); q.pop();
        answer.push_back(cur); 
        for (int nxt : adj[cur])
        {
            degree[nxt]--;
            if (degree[nxt] == 0) q.push(nxt);
        }
    }

    for (int i = 0; i < n; i++)
        cout << answer[i] << ' ';

    return 0;
}