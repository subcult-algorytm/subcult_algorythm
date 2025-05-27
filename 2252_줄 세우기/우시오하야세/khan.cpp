#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, M;

vector<int> adj[32001];
int inDegree[32001];
vector<int> result;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    for (int i = 0; i < M; ++i)
    {
        int x, y;
        cin >> x >> y;

        adj[x].push_back(y);
        inDegree[y]++;
    }

    queue<int> q;

    for (int i = 1; i <= N; ++i)
    {
        if (inDegree[i] == 0) q.push(i);
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        result.push_back(u);

        for (int v : adj[u])
        {
            inDegree[v]--;
            if (inDegree[v] == 0) q.push(v);
        }
    }

    for (int x : result) cout << x << " ";
}