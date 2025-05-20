#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// 정점은 최대 20000, 가중치는 최대 10이므로, INF의 최소값은 (20000-1)*10 + 1 = 199991 입니다
const int INF = 199991;

// v <= 20000, 인덱스를 1부터 시작한다고 하면, 1 + v + 1이 배열의 최소 크기입니다
vector<pair<int, int>> adj[20002];

// k 에서 다른 정점으로 가는 거리
int dist[20002];

// k에서의 가중치를 저장할 min 우선순위 큐
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. 초기화
    int v, e;
    cin >> v >> e;

    int k;
    cin >> k;
    fill(dist, dist + v + 1, INF);
    while (e--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
    }
	dist[k] = 0; // dist 초기화 순서 조심하기! (INF로 먼저 초기화 후, 시작점 [k]를 0으로 초기화)


    // 2. pq에 시작점 k의 가중치과 k를 넣고 다익스트라 시작
    // 이때, min heap으로 가중치가 가장 적은 값이 나옵니다. 
    // ------ { 가중치, 목적지 } -------
    pq.push({ dist[k], k });
    while (!pq.empty())
    {
        pair<int, int> cur = pq.top();
        pq.pop();

        // 현재 최단 거리와 pq에 값이 다르므로 생략합니다
        if (dist[cur.second] != cur.first) continue;

        // (1) pq에서 추출한 정점(cur.second)과 연결된 모든 정점(nxt.second)의 가중치(nxt.first)를 더한 경로와
        // dist에 저장되어 있는 값을 비교하여 dist배열에 넣은 후
        // (2)연결된 다른 정점(nxt)를 다음 검사를 위해 pq에 넣습니다
        for (pair<int, int> nxt : adj[cur.second])
        {
            // (1)
            if (dist[nxt.second] <= dist[cur.second] + nxt.first)
                continue;
            dist[nxt.second] = dist[cur.second] + nxt.first;
            // (2)
            pq.push({ dist[nxt.second], nxt.second });
        }
    }

    for (int i = 1; i <= v; i++)
    {
        if (dist[i] == INF)
            cout << "INF\n";
        else
            cout << dist[i] << '\n';
    }

    return 0;
}