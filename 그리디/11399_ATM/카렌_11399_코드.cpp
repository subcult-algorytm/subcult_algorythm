#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // 1. Vector 만들어 주기 

    int N;
    cin >> N;

    vector<int> P(N);
    for (int i = 0; i < N; i++) cin >> P[i];

    // 2. Vector 값들 오름차순으로 정렬 해 주기
    
    sort(P.begin(), P.end());

    // 3. 누적합과 전체합 계산 해 주기 

    int total = 0;
    int cur = 0;

    for (int i = 0; i < N; i++)
    {
        cur += P[i];
        total += cur;
    }

    cout << total << '\n';

    return 0;
}
 
