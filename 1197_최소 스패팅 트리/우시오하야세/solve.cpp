#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

int V, E, MST;

vector<pair<int, int>> edges[10001];
bool visit[10001];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> V >> E;

    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;

        edges[u].emplace_back(v, w);
        edges[v].emplace_back(u, w);
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, 1);
    while (!pq.empty())
    {
        int current = pq.top().second;
        int distance = pq.top().first;
        pq.pop();

        if (!visit[current])
        {
            visit[current] = true;
            int nodeNum = edges[current].size();
            MST += distance;

            for (int i = 0; i < nodeNum; ++i)
            {
                int nextNode = edges[current][i].first;
                int nextDist = edges[current][i].second;
                if (!visit[nextNode])
                {
                    pq.emplace(nextDist, nextNode);
                }
            }
        }
    }

    cout << MST;
}