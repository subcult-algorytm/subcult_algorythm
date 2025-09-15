#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
    int n; cin >> n;
    vector<pair<int, int>> vec(n);

    // { price, day } -> { day, price } 반대로
    for (int i = 0; i < n; i++)
        cin >> vec[i].second >> vec[i].first;

    sort(vec.begin(), vec.end()); // 오름차순

    priority_queue<int, vector<int>, greater<int>> pq; // min heap
    for (int i = 0; i < n; i++)
    {
        int d = vec[i].first;
        int p = vec[i].second;

        pq.push(p);
        
        if (pq.size() > d) pq.pop();
    }

    int ans = 0;
    while (!pq.empty())
    {
        ans += pq.top();
        pq.pop();
    }

    cout << ans;

    return 0;
}