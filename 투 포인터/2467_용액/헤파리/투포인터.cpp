#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(v.begin(), v.end());

    int l = 0;
    int r = n - 1;
    
    int ans1 = v[l];
    int ans2 = v[r];
    int sum = v[l] + v[r];
    while (l < r)
    {
        if (abs(sum) > abs(v[l] + v[r]))
        {
            ans1 = v[l];
            ans2 = v[r];
            sum = ans1 + ans2;
        }

        if (v[l] + v[r] > 0) r--;
        else l++;
    }

    cout << ans1 << ' ' << ans2;

    return 0;
}