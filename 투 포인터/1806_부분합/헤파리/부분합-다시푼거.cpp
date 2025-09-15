#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, s;
    cin >> n >> s; // s이상 찾기
    
    vector<int> a(n + 1, -1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    int ans = n + 1;
    int l = 1;
    int r = 0;
    int sum = 0;

    // r을 항상 증가
    while (true)
    {
        if (sum >= s)
        {
            ans = min(ans, r - l + 1);
            sum -= a[l++];
        }
        else if (r == n) break;
        else sum += a[++r];
    }

    if (ans == n + 1) cout << 0;
    else cout << ans;
}