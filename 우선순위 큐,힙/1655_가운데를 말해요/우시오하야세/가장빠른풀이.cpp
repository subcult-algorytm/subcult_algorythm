#include <iostream>
#include <string>
using namespace std;

char v[700000];
int p;
inline int f()
{
    int answer = 0, x = v[p++];
    bool flag = false;
    if (x == '-')
        flag = true;
    else
        answer = (x & 0x0F);

    while (1)
    {
        x = v[p++];
        if (x == '\n' || x == ' ') break;
        answer = answer * 10 + (x & 0x0F);
    }
    return flag ? -answer : answer;
}
int main(void)
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    fread(v, 1, 700000, stdin);
    int n = f(), arr[52769] = {0};
    string answer;

    for (int k = 1; k <= n; k++)
    {
        for (int t = (f() + 42768); t; t >>= 1) arr[t]++;
        int idx = 1, dx = (k + 1) / 2;
        while (!(idx & (1 << 15))) arr[idx << 1] >= dx ? idx <<= 1 : (dx -= arr[idx << 1], idx = ((idx << 1) | 1));
        answer += to_string(idx - 42768);
        answer.push_back('\n');
    }
    cout << answer;
    return 0;
}