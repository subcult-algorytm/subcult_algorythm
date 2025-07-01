#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int N, M;

void dfs(vector<int>& level, vector<vector<int>>& parent, vector<vector<int>>& adj, int cur, int cur_lvl,
         int parent_node)
{
    level[cur] = cur_lvl;

    for (auto& next : adj[cur])
    {
        if (next != parent_node)
        {
            parent[next][0] = cur;
            dfs(level, parent, adj, next, cur_lvl + 1, cur);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    vector<vector<int>> adj(N + 1);

    for (int i = 0; i < N - 1; ++i)
    {
        int p, c;
        cin >> p >> c;
        adj[p].push_back(c);
        adj[c].push_back(p);
    }

    int max_level = floor(log2(N));
    vector<vector<int>> parent(N + 1, vector<int>(max_level + 1));
    vector<int> level(N + 1);

    dfs(level, parent, adj, 1, 1, 0);

    for (int i = 1; i <= max_level; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            parent[j][i] = parent[parent[j][i - 1]][i - 1];
        }
    }
    cin >> M;

    for (int i = 0; i < M; ++i)
    {
        int a, b;
        cin >> a >> b;
        int a_level = level[a];
        int b_level = level[b];

        if (a_level < b_level) std::swap(a, b);

        for (int i = max_level; i >= 0; --i)
            if (level[a] - level[b] >= (1 << i))
            {
                a = parent[a][i];
            }
        if (a == b)
        {
            cout << a << '\n';
            continue;
        }

        for (int i = max_level; i >= 0; --i)
        {
            if (parent[a][i] != parent[b][i])
            {
                a = parent[a][i];
                b = parent[b][i];
            }
        }

        cout << parent[a][0] << '\n';
    }
}