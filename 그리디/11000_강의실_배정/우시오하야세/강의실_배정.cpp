#include <bits/stdc++.h>

#define FAST_IO                   \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);

using namespace std;

bool cmp(const pair<int, int>& a, const pair<int, int>& b)
{
    return a.second > b.second;
}

int N;

int main()
{
    FAST_IO;

    cin >> N;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> start_pq;
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> end_pq(cmp);

    for (int i = 0; i < N; ++i)
    {
        int s, e;
        cin >> s >> e;
        start_pq.push({s, e});
    }

    int result = 0;

    while (!start_pq.empty())
    {
        auto x = start_pq.top();
        start_pq.pop();

        end_pq.push(x);
        if (end_pq.top().second <= x.first) end_pq.pop();
        result = max(result, (int)end_pq.size());
    }

    cout << result;
}
