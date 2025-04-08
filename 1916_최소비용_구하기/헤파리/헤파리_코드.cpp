#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int dist[1002];
vector<pair<int, int>> adj[1002]; // { 가중치, 정점 }

const int INF = (1000 - 1) * 100000;
// const int INF = (1000 - 1) * 100000 - 1;

int main()
{
    // 1. 초기화
    int v, e;
    cin >> v;
    cin >> e;
    fill(dist, dist + v + 1, INF);

    while (e--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
    }

    int st, ed;
    cin >> st >> ed;
    
    // 2. 다익스트라
    dist[st] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 밑에서 검사를 하지만, 원칙적으로는 min heap을 사용해야함
    pq.push({ 0, st });
    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();

        if (dist[cur.second] != cur.first) continue; // q.v의 dist != q.dist
        for (auto nxt : adj[cur.second])
        {
            if (dist[nxt.second] <= dist[cur.second] + nxt.first) continue; // q.v의 dist <= q.dist + q.nxt
            dist[nxt.second] = dist[cur.second] + nxt.first;
            pq.push({ dist[nxt.second], nxt.second });
        }
    }

    cout << dist[ed];
    return 0;
}