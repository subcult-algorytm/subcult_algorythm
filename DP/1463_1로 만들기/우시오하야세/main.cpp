#include <iostream>
#include <numeric>

int N, M;
int dp[static_cast<int>(1e+6) + 1];

int func(int num, int repeatCnt)
{
    if (num < 2)
        return repeatCnt;

    return std::min(func(num / 2, repeatCnt + 1 + num % 2), func(num / 3, repeatCnt + 1 + (num % 3)));
}
int main()
{
    std::cin >> N;

    std::cout << func(N, 0);
}
