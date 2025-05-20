#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

int V, E, startVertex;

vector<pair<int, int>> edges[20'001];
int dist[20'001];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> V >> E;

    cin >> startVertex;

    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;

        edges[u].emplace_back(v, w);
    }

    const int intMax = numeric_limits<int>::max();

    for (int i = 1; i <= V; ++i) dist[i] = intMax;

    priority_queue<pair<int, int>> pq;
    pq.emplace(0, startVertex);

    dist[startVertex] = 0;

    while (!pq.empty())
    {
        int current = pq.top().second;
        int distance = -pq.top().first;
        pq.pop();

        if (dist[current] < distance) continue;

        int nodeNum = edges[current].size();

        for (int i = 0; i < nodeNum; ++i)
        {
            int nextNode = edges[current][i].first;
            int nextDist = distance + edges[current][i].second;
            if (nextDist < dist[nextNode])
            {
                dist[nextNode] = nextDist;
                pq.emplace(-nextDist, nextNode);
            }
        }
    }

    for (int i = 1; i <= V; ++i)
        if (dist[i] == intMax)
            cout << "INF" << "\n";
        else
            cout << dist[i] << '\n';
}
