#include <iostream>
#include <algorithm>
using namespace std;

/*
dp[10] = min(dp[10/3] + 1, dp[10/2] + 1, dp[10-1] + 1)
-> dp[n] = min(dp[n/3] + 1, dp[n/2] + 1, dp[n-1] + 1)
*/

int dp[1000001];

int main(void)
{
	int n; 
    cin >> n;

    // 초기화 (base case)
    dp[0] = 0; 
    dp[1] = 0; 

	for (int i = 2; i <= n; i++)
	{
        // 기본값 : 우선 i-1에서 오는 경우로 초기화
        dp[i] = dp[i - 1] + 1;

		if (i % 3 == 0)
			dp[i] = min(dp[i], dp[i / 3] + 1);

		if (i % 2 == 0)
			dp[i] = min(dp[i], dp[i / 2] + 1);
	}

    cout << dp[n]; 
}