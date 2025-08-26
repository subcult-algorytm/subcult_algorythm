#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> v(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> v[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + v[i][j];

    int k; cin >> k;
    while (k--)
    {
        int i, j, x, y;
        cin >> i >> j >> x >> y;
        // 현재 사각형 - 위쪽 - 왼쪽 + 왼쪽위 2번 빠진곳 복구
        cout << s[x][y] - s[i-1][y] - s[x][j-1] + s[i-1][j-1] << '\n';
    }
    
    return 0;
}