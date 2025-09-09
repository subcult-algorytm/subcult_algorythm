#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    #define int long long
    int n; cin >> n;
    vector<int> v(n, 0);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v.begin(), v.end());

    int sum = LLONG_MAX;
    int ans1, ans2, ans3;
    // m포인터를 앞에 고정해두고, 투포인터 돌리기
    for (int m = 0; m < n - 2; m++)
    {
        int l = m + 1;
        int r = n - 1;
        while (l < r)
        {
            if (abs(v[m] + v[l] + v[r]) < sum)
            {
                sum = abs(v[m] + v[l] + v[r]);
                ans1 = v[m];
                ans2 = v[l];
                ans3 = v[r];
            }

            if ((v[m] + v[l] + v[r]) > 0) r--;
            else l++;
        }
    }
    
    cout << ans1 << ' ' << ans2 << ' ' << ans3;

    return 0;
}