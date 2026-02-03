#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> wine(n+1);
    vector<int> dp(n+1);
    
    for(int i = 1; i <=n ; i++)
    {
        cin >> wine[i];
    }
    
    // 1,2 초기화 
     
    dp[1] = wine[1];
    
    // 1 입력 했을 경우 오류 방지 
    
    if(n>1)
    {
        dp[2] = wine[1] + wine[2];
    }
    
    // max 함수 이용하여 dp 채워주기 
     
    for(int i = 3; i <= n ; i++)
    {
        dp[i] = max({dp[i-1],dp[i-2]+wine[i],dp[i-3]+wine[i-1]+wine[i]});
    }
    
    cout << dp[n] << endl; 
    
    return 0; 
}
