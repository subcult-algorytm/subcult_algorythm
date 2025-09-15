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
    long long min = numeric_limits<long long>::max() - 1;

    arr.resize(N);

    for (int i = 0; i < N; ++i) cin >> arr[i];

    sort(arr.begin(), arr.end());

    for (int i = 0; i < N - 2; ++i)
    {
        int left = i + 1;
        int right = N - 1;

        while (left < right)
        {
            if (abs(arr[left] + arr[right] + arr[i]) <= min)
            {
                min = abs(arr[left] + arr[right] + arr[i]);
                answer[0] = arr[i];
                answer[1] = arr[left];
                answer[2] = arr[right];
            }
            if (arr[left] + arr[right] + arr[i] < 0LL)
                left++;
            else if (arr[left] + arr[right] + arr[i] > 0LL)
                right--;
            else
            {
                cout << arr[i] << ' ' << arr[left] << ' ' << arr[right];
                exit(0);
            }
        }
    }

    for (auto i : answer) cout << i << ' ';
}