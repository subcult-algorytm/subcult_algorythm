#include <iostream>
#include <limits>
#include <queue>

using namespace std;

int N;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    int mid;

    cin >> mid;
    cout << mid << '\n';

    int i = 1;

    priority_queue<int, vector<int>, greater<int>> max_pq;
    priority_queue<int> min_pq;

    while ((max_pq.size() == 0 || min_pq.size() == 0) && i < N)
    {
        int a;
        cin >> a;
        if (max_pq.size() == 0)
        {
            if (a >= mid)
                max_pq.push(a);
            else
            {
                max_pq.push(mid);
                mid = a;
            }
        }
        else if (min_pq.size() == 0)
        {
            if (a > max_pq.top())
            {
                max_pq.push(a);
                min_pq.push(mid);
                mid = max_pq.top();
                max_pq.pop();
            }
            else if (a <= max_pq.top() && a > mid)
            {
                min_pq.push(mid);
                mid = a;
            }
            else if (a <= mid)
                min_pq.push(a);
        }
        cout << mid << '\n';
        ++i;
    }

    for (; i < N; ++i)
    {
        int x;
        cin >> x;
        if (x >= max_pq.top())
        {
            if (max_pq.size() > min_pq.size())
            {
                max_pq.push(x);
                min_pq.push(mid);
                mid = max_pq.top();
                max_pq.pop();
            }
            else
                max_pq.push(x);
        }
        else if (x <= min_pq.top())
        {
            if (max_pq.size() <= min_pq.size())
            {
                min_pq.push(x);
                max_pq.push(mid);
                mid = min_pq.top();
                min_pq.pop();
            }
            else
                min_pq.push(x);
        }
        else if (x < mid && x > min_pq.top())
        {
            if (max_pq.size() <= min_pq.size())
            {
                max_pq.push(mid);
                mid = x;
            }
            else
            {
                min_pq.push(x);
            }
        }
        else if (x >= mid && x < max_pq.top())
        {
            if (min_pq.size() < max_pq.size())
            {
                min_pq.push(mid);
                mid = x;
            }
            else
            {
                max_pq.push(x);
            }
        }

        cout << mid << '\n';
    }
}