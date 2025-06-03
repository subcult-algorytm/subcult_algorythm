#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> p(100, -1);
vector<int> party[100];

int find(int x)
{
    if (p[x] < 0)
        return x;

    return p[x] = find(p[x]); // path compression
}

bool union_(int u, int v)
{
    u = find(u); v = find(v);
    
    if (u == v) return false; // { u, v, ... } : 이미 같은 집합
    if (p[u] == p[v]) p[u]--; // tree + 1
    if (p[u] > p[v]) swap(u, v); 
    p[v] = u;

    return true;
}


int main()
{
    int n, m;
    cin >> n >> m; // 사람, 파티

    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int tn;
        cin >> tn;

        union_(0, tn); // 진실을 사는 사람들을 0집합에 묶기 { 0, 1, 2, 3, 4} true
    }

    // 1. 정보가 퍼지기 전, 각 파티의 집합 생성
    for (int i = 1; i <= m; i++)
    {
        cin >> t;
        for (int j = 0; j < t; j++)
        {
            int nn;
            cin >> nn;
            party[i].push_back(nn);
            if (j > 0)
                union_(party[i][j-1], nn);
        }
    }

    // 2. 파티 집합을 모두 순회하면서, 거짓이 퍼진 집합을 찾아냄
    int ans = m;
    for (int i = 1; i <= m; i++)
    {
        if(find(party[i][0]) == find(0)) // 각 파티 집합이 0번 거짓 집합과 같은 집합인지 확인
            ans--; // 같다면 정답에서 제외
    }

    cout << ans;
}