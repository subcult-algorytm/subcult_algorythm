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
// C++의 priority_queue는 기본적으로 max heap이므로, min heap으로 사용하기 위해 greater 사용합니다
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
    // (이 루프는 모든 간선을 검사하므로, 시간복잡도가 ElogV 입니다)
    pq.push({ dist[k], k }); // {0, k}

    while (!pq.empty())
    {
        // 현재 가장 짧은 거리를 가진 정점 정보를 꺼냅니다
        pair<int, int> cur = pq.top();
        pq.pop();

        // 이미 처리된 정점이거나, pq에 저장된 거리보다 더 짧은 경로가 이미 발견된 경우 스킵
        // - (pq에는 같은 정점에 대한 정보가 여러 번 들어갈 수 있으며, 그 중 가장 작은 값만 유효합니다)
        // dist[]는 해당 정점까지의 '확정된' 최단 거리
        // cur.first는 pq에 삽입될 '당시의' 최단 거리 후보
        if (dist[cur.second] != cur.first) continue;

        
        // 현재 정점(cur.second)과 연결된 모든 인접 정점(nxt.second)들을 순회하며
        // 시작점 K로부터 각 인접 정점까지의 최단 거리를 갱신할 수 있는지 확인합니다 (Relaxation 과정)
        for (pair<int, int> nxt : adj[cur.second]) 
        {
            // (1) [시작점 K -> nxt.second (인접 정점)] == dist[nxt.second]
            //     [시작점 K -> cur.second (현재 정점) -> nxt.second (인접 정점)] == dist[cur.second] + nxt.first)
            //     현재 정점을 경유하여 갔을때 이득이 없으므로, 다음 인접 정점으로 넘어갑니다
            if (dist[nxt.second] <= dist[cur.second] + nxt.first) continue;
                
            // (2) 경유하여 가는게 이득이라면?
            //     => dist[nxt.second] 값을 [k에서 cur.second까지의 최단 거리 + cur.second에서 nxt.second까지의 간선 가중치]로 업데이트합니다.
            //     => 새로운 최단 거리 정보 ({ 새로운 거리, nxt.second })를 찾았으므로 pq에 추가합니다
            //     이렇게해서 nxt.second를 기준으로 하는 더 빠른른 경로가 이후에 탐색될 수 있도록 합니다 - (그리디)
            dist[nxt.second] = dist[cur.second] + nxt.first;
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