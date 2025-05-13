
#include <cmath>
#include <iostream>
#include <numeric>
using namespace std;

constexpr int INF = numeric_limits<int>::max();

int N, S;

int arr[100001];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> S;

    for (int i = 1; i <= N; ++i)
    {
        cin >> arr[i];
        arr[i] += arr[i - 1];
    }

    int len = INF;

    int first = 1;
    int second = 1;

    while (second != N + 1)
    {
        int sum = arr[second] - arr[first - 1];
        if (sum >= S)
        {
            len = second - first + 1 < len ? second - first + 1 : len;
            first++;
        }
        else
            second++;
    }

    cout << ((len != INF) ? len : 0);
}
