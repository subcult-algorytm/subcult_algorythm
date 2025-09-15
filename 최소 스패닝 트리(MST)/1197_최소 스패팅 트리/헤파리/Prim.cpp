#include <iostream>
#include <set>
#include <algorithm>
#include <queue>
#include <vector>
#include <tuple>
using namespace std;

int v, e;
vector<pair<int, int>> adj[10005]; // { weight, vertex }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> v >> e;

    for (int i = 0; i < e; i++) 
    {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({ w, b }); 
        adj[b].push_back({ w, a }); // (무방향)
    }

    // 초기화
    bool chk[10005] = { false }; 
    int cnt = 0; 
    long long ans = 0; 

    // max heap - 가중치 기준 오름차순 정렬
    priority_queue<tuple<int, int, int>,
        vector<tuple<int, int, int>>,
        greater<tuple<int, int, int>>> pq;

    // 1번 정점에서 시작
    chk[1] = true;
    for (auto nxt : adj[1]) 
    {
        int w = nxt.first;
        int next_vertex = nxt.second;
        pq.push({ w, 1, next_vertex }); // {가중치, 현재정점, 다음정점}
    }

    while (cnt < v - 1) 
    {
        int w, a, b;
        tie(w, a, b) = pq.top();
        pq.pop();
        
        if (chk[b]) continue; // 이미 MST에 포함된 정점이면 스킵
        
        // 새로운 정점 추가
        chk[b] = true;
        cnt++;
        ans += w; // 가중치 누적

        // 새로 추가된 정점(b)의 인접 간선 탐색
        for (auto nxt : adj[b]) 
        {
            int nw = nxt.first;
            int nv = nxt.second;

            // 아직 방문하지 않은 정점만 큐에 추가
            if (!chk[nv]) 
            {
                pq.push({ nw, b, nv });
            }
        }
    }

    cout << ans;
}