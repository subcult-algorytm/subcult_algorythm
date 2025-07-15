#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100001;
const int LOGN = 17;

vector<int> adj[MAXN]; // ���� ����Ʈ�� Ȱ���� Ʈ��
int parent[MAXN][LOGN]; // parent[i][j] : i��° ����� 2^j ��° ����
int depth[MAXN];

// ���� �켱 Ž��(DFS)�� ����Ͽ� �� ����� ���̿� �θ� �˾Ƴ���.
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

// ���� ������(binary lifting)�� ���� parent �迭�� ä���ش�.
void set_parent(int n)
{
    dfs(1, 0, 0);
    
    for (int j = 1; j < LOGN; ++j) {
        for (int i = 1; i <= n; ++i) {
            // ��ȭ�� ���
            // i�� ����� 2^j ��° ������ i�� ����� 2^(j-1) ��° ������ 2^(j-1) ��° ����� ����.
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
        }
    }
}

// �� ��� u, v�� LCA�� ã���ش�.
int lca(int u, int v)
{
    // 1. �� ����� ���̸� �����. �׻� u�� �� ���� swap �Լ��� ����Ѵ�.
    if (depth[u] < depth[v])
    {
        swap(u, v);
    }

    // 2. u�� v�� ���� ���̷� �ø���.
    for (int j = LOGN - 1; j >= 0; --j) 
    {
        if (depth[u] - depth[v] >= (1 << j)) {
            u = parent[u][j];
        }
    }

    // 3. ���̸� ���߰� �� ��尡 ������, �� ��尡 lca �̴�.
    if (u == v)
    {
        return u;
    }
    // 4. �� ��尡 �������� ���� ���� ���ÿ� �����Ѵ�.
    for (int j = LOGN - 1; j >= 0; --j)
    {
        if (parent[u][j] != parent[v][j])
        {
            u = parent[u][j];
            v = parent[v][j];
        }
    }

    // 5. �ٷ� �� �θ� LCA �̴�.
    return parent[u][0];
}

// main �Լ� �κ�
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
