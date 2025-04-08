#include <algorithm>
#include <iostream>
#include <memory.h>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

int N, M, start, _end;

vector<pair<int, int>> arr[1001];
int dist[1001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

void dijkstra()
{
    while (!pq.empty())
    {

        auto nowNode = pq.top();
        pq.pop();

        int node = nowNode.second;
        int weightSum = nowNode.first;

        if (dist[node] < weightSum)
            continue;

        for (int i = 0; i < arr[node].size(); ++i)
        {
            int nextNode = arr[node][i].first;
            int weight = arr[node][i].second;

            if (dist[nextNode] > weight + weightSum)
            {
                dist[nextNode] = weight + weightSum;

                pq.push({dist[nextNode], nextNode});
            }
        }
    }
}

int main()
{
    cin >> N >> M;

    for (int i = 1; i <= N; ++i)
        dist[i] = INF;

    for (int i = 0; i < M; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;

        arr[a].emplace_back(b, c);
    }

    cin >> start >> _end;

    pq.emplace(0, start);
    dist[start] = 0;

    dijkstra();

    cout << dist[_end];
}
