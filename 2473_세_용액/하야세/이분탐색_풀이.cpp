#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int N;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    vector<long long> arr;
    vector<long long> answer;
    answer.resize(3);
    long long min = numeric_limits<long long>::max();

    arr.resize(N);

    for (int i = 0; i < N; ++i) cin >> arr[i];

    sort(arr.begin(), arr.end());

    for (int i = 0; i < N; ++i)
    {
        long long left = arr[i];
        for (int j = N - 1; j > i; --j)
        {
            long long right = arr[j];
            auto middle1 = lower_bound(arr.begin() + i + 1, arr.begin() + j, -(left + right));
            auto middle2 = middle1 - 1;

            if (abs(left + right + *middle1) < min && right != *middle1)
            {
                min = abs(left + right + *middle1);
                answer[0] = left;
                answer[1] = *middle1;
                answer[2] = right;
            }
            if (abs(left + right + *middle2) < min && left != *middle2)
            {
                min = abs(left + right + *middle2);
                answer[0] = left;
                answer[1] = *middle2;
                answer[2] = right;
            }
        }
    }

    for (int i : answer) cout << i << ' ';
}