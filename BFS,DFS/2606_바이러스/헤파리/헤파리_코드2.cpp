#include <iostream>
using namespace std;

int parent[1002];
int sz[1002];

// 재귀로 부모 찾기
int find(int x) 
{
    if (parent[x] == x) return x; 
    return parent[x] = find(parent[x]); // 경로압축
}

// 병합
void union_(int a, int b) 
{
    a = find(a);
    b = find(b);
    if (a == b) return; // 이미 같은 부모

    if (sz[a] < sz[b]) swap(a, b); // a에 더 큰 집합
    parent[b] = a; // b의 부모를 a로
    sz[a] += sz[b]; // a집합의 크기 증가
}

int main() 
{
    int n, p;
    cin >> n >> p;
    
    // 초기화
    for (int i = 1; i <= n; ++i) 
    {
        parent[i] = i;
        sz[i] = 1;
    }
    
    // 입력
    while (p--) 
    {
        int v, u;
        cin >> v >> u;
        union_(v, u);
    }
    
    int root = find(1);
    cout << sz[root] - 1;
    
    return 0;
}