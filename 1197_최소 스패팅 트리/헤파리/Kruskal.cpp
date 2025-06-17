#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

vector<int> p(10005, -1);

int find(int x)
{
    if (p[x] < 0) return x; // base condition
    return p[x] = find(p[x]); // path compression
}

bool union_(int u, int v)
{
    u = find(u);
    v = find(v);

    if (u == v) return false;

    if (p[u] == p[v]) p[u]--; // rank + 1
    if (p[u] > p[v]) swap(u, v); // union by rank

    p[v] = u;

    return true;
}

int v, e;
tuple<int, int, int> edge[100005]; // 인접리스트도 가능, 가중치 정렬 편의를 위해 tuple 사용

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> v >> e;

    int a, b, w;
    for (int i = 1; i <= e; i++)
    {
        cin >> a >> b >> w;
        edge[i] = { w, a, b };
    }

    // 1. sort by edge
    sort(edge + 1, edge + e + 1); // 1 - indexing

    int cnt = 0;
    int ans = 0;

    // 2. Kruskal
    for (int i = 1; i <= e; i++)
    {
        tie(w, a, b) = edge[i];
        if (union_(a, b))
        {
            ans += w; // 유니온 성공, edge의 가중치 추가
            cnt++;
        }
        if (cnt == v - 1) break; // MST는 vertex-1 만큼 edge가 만들어짐
    }
    cout << ans;
}