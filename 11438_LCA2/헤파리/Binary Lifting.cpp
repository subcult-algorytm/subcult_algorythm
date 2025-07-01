// O(N + M*log(N))

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 100001;
const int LOG_MAX_N = 17; // N <= 100000 을 기준으로, 2^16 < 100,000 < 2^17. 최대 17번 
vector<int> adj[MAX_N]; // 트리
int parent[LOG_MAX_N][MAX_N]; // parent[k][i] : i의 2^k번째 조상
int depth[MAX_N];

// DFS로 각 노드의 깊이와 직속 부모(Base Case; parent[0][i]) 계산
void dfs(int here, int p, int d)
{
    depth[here] = d;
    parent[0][here] = p;

    for (int there : adj[here])
    {
        if (there == p) continue; // 부모 노드로 돌아가지 않도록 스킾
        dfs(there, here, d + 1);
    }
}

// 전체 부모 관계 설정 - 전처리
void set_parent(int n)
{
    // 1. DFS로 depth와 parent[0] 배열 채우기
    dfs(1, 0, 1); // 1번 노드를 루트로

    // 2. parent[k][i]를 DP로 채우기 
    // parent[k][i] = parent[k-1][parent[k-1][i]]
    for (int k = 1; k < LOG_MAX_N; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            // i의 2^(k-1)번째 조상이 존재한다면
            if (parent[k-1][i] != 0)
                parent[k][i] = parent[k-1][parent[k-1][i]];
        }
    }
}

// 두 노드 u,v의 LCA 찾기
int lca(int u, int v)
{
    // 1. u가 더 깊은 노드가 되도록 swap
    if (depth[u] < depth[v]) swap(u, v); 

    // 2. 두 정점의 깊이 맞추기
    for (int k = LOG_MAX_N - 1; k >= 0; k--)
    {
        // u,v의 깊이 차이가 2^k보다 크거나 같다면
        if (depth[u] - depth[v] >= (1 << k))
            u = parent[k][u];
    }

    // 3. 만약 두 노드가 같다면, v가 u의 조상
    if (u == v)
        return u; // (또는 v)

    // 4. 두 정점을 부모 방향으로 동시에 올라가면서 LCA바로 아래까지 탐색
    for (int k = LOG_MAX_N - 1; k >= 0; k--)
    {
        if (parent[k][u] != parent[k][v])
        {
            u = parent[k][u];
            v = parent[k][v];
        }
    }

    return parent[0][u]; // u(또는 v)의 부모가 LCA
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // 트리 생성
    for (int i = 0; i < n-1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 전처리 O(N log N)
    set_parent(n);

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i) 
    {
        int u, v;
        cin >> u >> v;
        // 쿼리당 O(log N)
        cout << lca(u, v) << '\n';
    }

    return 0;
}
