#include <iostream>
#include <queue>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    
    priority_queue<int> max_pq;
    priority_queue<int, vector<int>, greater<int>> min_pq;

    while (n--)
    {
        int x; cin >> x;
        
        // 중심을 기준으로 양쪽으로 나누고, 항상 왼쪽이 1개 더 많거나 같게 유지 { 1 2 3 } { 6 5 4}
        if (max_pq.size() == min_pq.size()) max_pq.push(x);
        else min_pq.push(x);

        // 값 조정
        if (!max_pq.empty() && !min_pq.empty() && max_pq.top() > min_pq.top())
        {
            int max_top = max_pq.top(); max_pq.pop();
            int min_top = min_pq.top(); min_pq.pop();

            max_pq.push(min_top);
            min_pq.push(max_top);
        }

        cout << max_pq.top() << '\n';
    }
}

// O(n log n)