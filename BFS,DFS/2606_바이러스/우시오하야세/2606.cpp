#include <iostream>
#include <vector>

using namespace std;

int N, M, a, b;

vector<int> v[101];
int virus[101];
int ans;

void dfs(int x)
{
    for (int i = 0; i < v[x].size(); i++)
    {
        int k = v[x][i];

        if (virus[k] == 0)
        {
            virus[k] = 1;
            ans++;
            dfs(k);
        }
    }

    return;
}

int main()
{

    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        cin >> a >> b;

        v[a].push_back(b);
        v[b].push_back(a);
    }

    virus[1] = 1;
    dfs(1);

    cout << ans;

    return 0;
}