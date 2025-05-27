#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int N, M;

vector<vector<int>> adj;
vector<bool> visit;
vector<int> result;

void dfs(int x)
{
    visit[x] = true;

    // 현재 연결된 간선 방문
    for (int y = 0; y < adj[x].size(); ++y)
        if (!visit[adj[x][y]]) dfs(adj[x][y]);

    result.push_back(x);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    adj.resize(N + 1);
    visit.resize(N + 1);

    /* 입력 받기 */
    for (int i = 0; i < M; ++i)
    {
        int x, y;
        cin >> x >> y;

        adj[x].push_back(y);
    }

    // 모든 정점에 대해 방문.
    // 들어오는 정점은
    // dfs함수에서 방문하지 않을 수도 있음
    // 따라서 전체 반복문으로 정점들을 한번씩 방문해야함
    for (int i = 1; i <= N; ++i)
        if (!visit[i]) dfs(i);

    // 마지막에 끝나는 걸 가장 먼저 찾아 저장했기 때문에
    // 순서가 거꾸로 저장되어 있음
    // 따라서 뒤집어 줘야 옳은 순서가 됌
    reverse(result.begin(), result.end());

    for (auto x : result) cout << x << ' ';
}
