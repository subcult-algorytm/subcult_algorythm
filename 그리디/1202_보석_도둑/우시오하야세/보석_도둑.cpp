#include <algorithm>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

int N, K;
deque<pair<size_t, size_t>> pq;
map<size_t, size_t> weight;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;

    for (int i = 0; i < N; ++i)
    {
        size_t m, v;
        cin >> m >> v;

        pq.emplace_back(v, m);
    }

    for (int i = 0; i < K; ++i)
    {
        size_t c;
        cin >> c;

        if (weight.find(c) == weight.end())
            weight.insert({c, 1});
        else
            weight[c] += 1;
    }

    sort(pq.begin(), pq.end());

    size_t result = 0;

    while (!pq.empty() && !weight.empty())
    {
        const auto jewelry = pq.back();

        auto iter = weight.lower_bound(jewelry.second);

        if (iter != weight.end())
        {
            if (iter->second == 1)
                weight.erase(iter);
            else
                weight[iter->first] -= 1;
            result += jewelry.first;
        }
        pq.pop_back();
    }

    cout << result;
}