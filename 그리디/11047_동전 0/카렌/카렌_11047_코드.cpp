#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // N : 동전의 종류 , K : 문제에서 채워야 하는 총액

    int N,K;
    cin >> N >> K;

    vector<int> coins(N);

    for(int i = 0; i < N; i++)
    {
        cin >> coins[i];
    } 

    int count = 0;

    for(int i = N-1 ; i >= 0; i--)
    {
        count += K/coins[i];

        K %= coins[i];


    if( K == 0)
        {
            break;
        }
    }
    cout << count << "\n";

    return 0;
}
