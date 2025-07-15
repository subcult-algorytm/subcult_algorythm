#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100001;
const int LOGN = 17;

vector<int> adj[MAXN]; // 인접 리스트를 활용한 트리
int parent[MAXN][LOGN]; // parent[i][j] : i번째 노드의 2^j 번째 조상
int depth[MAXN];

// 깊이 우선 탐색(DFS)을 사용하여 각 노드의 깊이와 부모를 알아낸다.
void dfs(int curr, int p, int d)
{
    depth[curr] = d;
    parent[curr][0] = p;
    for (int next : adj[curr]) {
        if (next != p) {
            dfs(next, curr, d + 1); 
        }
    }
}

// 이진 리프팅(binary lifting)을 위해 parent 배열을 채워준다.
void set_parent(int n)
{
    dfs(1, 0, 0);
    
    for (int j = 1; j < LOGN; ++j) {
        for (int i = 1; i <= n; ++i) {
            // 점화식 사용
            // i번 노드의 2^j 번째 조상은 i번 노드의 2^(j-1) 번째 조상의 2^(j-1) 번째 조상과 같다.
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
        }
    }
}

// 두 노드 u, v의 LCA를 찾아준다.
int lca(int u, int v)
{
    // 1. 두 노드의 깊이를 맞춘다. 항상 u가 더 깊도록 swap 함수를 사용한다.
    if (depth[u] < depth[v])
    {
        swap(u, v);
    }

    // 2. u와 v를 같은 깊이로 올린다.
    for (int j = LOGN - 1; j >= 0; --j) 
    {
        if (depth[u] - depth[v] >= (1 << j)) {
            u = parent[u][j];
        }
    }

    // 3. 깊이를 맞추고 두 노드가 같으면, 그 노드가 lca 이다.
    if (u == v)
    {
        return u;
    }
    // 4. 두 노드가 같아지기 직전 까지 동시에 점프한다.
    for (int j = LOGN - 1; j >= 0; --j)
    {
        if (parent[u][j] != parent[v][j])
        {
            u = parent[u][j];
            v = parent[v][j];
        }
    }

    // 5. 바로 위 부모가 LCA 이다.
    return parent[u][0];
}

// main 함수 부분
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    set_parent(n);

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }

    return 0;
}
