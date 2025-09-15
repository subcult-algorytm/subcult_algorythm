#include <iostream>
#include <algorithm>
using namespace std;

int arr[100001];

int main()
{
    int n, s;
    cin >> n >> s;
    
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    
    int st = 1;
    int ed = 1;
    int ans = n+1;
    int sum = arr[1];
    while(st <= ed && ed <= n)
    {
        
        if (sum < s)
            sum += arr[++ed]; 
        else
        {
            ans = min(ans, ed-st+1); 
            sum -= arr[st++]; 
        }
    }
    
    if (ans == n+1)
        cout << 0;
    else
        cout << ans;
    
    return 0;
}