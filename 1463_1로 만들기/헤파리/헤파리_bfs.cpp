#include <iostream>
#include <queue>
#include <vector>
#include <algorithm> 
using namespace std;

const int MAX = 1000001;
int dist[MAX];         
int main(void)
{
    int n;
    cin >> n;

    // 1. 초기화
    fill(dist, dist + MAX, -1); 
    queue<int> q;
    dist[n] = 0; // 시작점 N의 거리는 0
    
    // 2. BFS 
    q.push(n);
    while (!q.empty()) 
    {
        int current = q.front();
        q.pop();

        // 1까지 오면 dist[1]의 거리를 출력하고 BFS를 끝냅니다.
        if (current == 1) 
        {
            cout << dist[1] << '\n';
            return 0; 
        }

        // 다음 가능한 상태들을 탐색
        // 저희가 사용하던 n/s/w/e 경로를 0/1/2 의 3가지 옵션(케이스)로 바꾸고
        // { 0, 1, 2 }
        // 각각의 옵션들에 연산 -1, /2, /3 을 매칭합니다.
        // -> 이 부분을 -1 경로 /2 경로 /3 경로로 나아간다라고 접근하시면 편합니다.
        int dOpt[3];
        int opt = 0;
        
        // opt : calc
        // 단 각 연산에서 연산이 가능한지는 if로 검사해야합니다. 
        
        // opt1 : -1
        if (current - 1 >= 1) 
            dOpt[opt++] = current - 1;
        
        // opt2 : /2
        if (current % 2 == 0 && current / 2 >= 1) 
            dOpt[opt++] = current / 2;
        
        // opt3 : /3
        if (current % 3 == 0 && current / 3 >= 1) 
            dOpt[opt++] = current / 3;
        

        // 각 옵션을 확인
        for (int i = 0; i < opt; ++i) 
        {
            int next = dOpt[i];
            if (dist[next] == -1) 
            {
                dist[next] = dist[current] + 1; 
                q.push(next);                   
            }
        }
    }
}