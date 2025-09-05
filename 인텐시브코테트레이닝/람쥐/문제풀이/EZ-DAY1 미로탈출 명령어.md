
**카카오 2023 블라인드 채용 - 6번 문제** 

카카오 공식 풀이 - https://tech.kakao.com/posts/567

### 난이도 

카카오 블로그에서는 난이도상 상위권 어려운 문제라 했으나.. 이진트리가 더 어려워 보입니다;;; 이 문제는 어렵다기보다는 문제가 꼬이면 한도끝도 없이 꼬여 시간배분을 망할 수있다고 보는게 더 맞을거 같습니다. 

Lvl 3의 무난한 난이도로, 카카오에서는 상위권으로 책정했으나, 기본적인 순회, 그리디만 잘 적용하면 풀수있어, 중간급 문제라고 보는게 맞을거 같습니다. 클라 코테의 단골주제기 때문에 중간급 문제가 유력합니다.


### DFS vs 그리디

결론적으로 그리디가 편한 풀이입니다. DFS는 최소 경로가 보장되지 않기 때문에 풀이가 꼬일 위험이 매우 큽니다. 

조건과 이동거리가 이미 정해져있다는것을 이용해야하고, 사전 순서대로 d > l >R  >u 의 순서로 우선순위를 가진다는것을 주목하면 됩니다. DFS는 최소경로 내지는 사전순서의 경로 탐색이 보장되지 않으므로 어렵습니다. 

다만 그리디는 조건에 맞는 최소경로를 어떻게 보장하는지에 대해 수동으로 로직을 설계해야하므로, 설계난이도가 조금 어려울 수 있습니다.


### 풀이 방법 

그래프가 출력이 되어있어 그래프를 출력할 필요가 있어보일거 같지만 아닙니다. 
**시작점과 끝점.** 이 부분만 유효한 정보기 때문에 2차원 배열을 만들어서 그래프를 만드는 건 하지 맙시다...

전형적인 그래프 순회 문제라고 생각하고 DFS을 적용하면 되지만, 여기서는 주목할 점이 있습니다. 

- 탐색 거리가 이미 주어진다는 것이며, 
- 최소 탐색거리보다 높은 탐색거리가 주어지면 그 탐색거리를 모두 소진해야한다는 것입니다. 
즉, 중도에 목적지까지 탐색이 되었다고 멈추는것이 아닌, 계속 탐색을 해야한다는 것으로, 
중도에 목적지까지 탐색시 다른 지점으로 간 뒤, 다시 돌아와야 합니다. 

그렇기 때문에 `주어진 탐색숫자-최단거리 탐색 숫자` 가 홀수이면 최단거리를 찍은 뒤에 돌아올 수 없으므로, 

```cpp
   int TravelLength = getDistance(x, y, r, c); 
    if (TravelLength > k || (k - TravelLength) % 2 != 0)
        return "impossible"; 
```

이에 대한 예외처리가 필수적입니다. 

그리고 d가 먼저 우선이 되므로, 최대한 아래로 먼저 이동하고, 최단거리를 찍고 지정된 탐색거리가 남으면 좌우 왕복및 마지막 상향이동으로 모든 탐색횟수를 소진하고 목표지점에  도달해야합니다.


### 그리디 풀이 

```cpp 

#include <string>
#include <algorithm>

using namespace std;

int getDist(int x, int y, int r, int c)
{
    return abs(x - r) + abs(y - c);
}


string solution(int n, int m, int x, int y, int r, int c, int k) 
{
    string answer = "";
    
    
    // 디스턴스 계산과 예외처리는 모두 같음
    int dist = getDist(x, y, r, c);
    
    if (dist > k || (k - dist) % 2 != 0)
        return "impossible";
    
    
    // 그리디로 이동횟수 소진전까지 현재 지점과 목표지점까지 Distance 계산후 최적 경로 배열에 추가. 
    // 아래로 최대한 많이 가고, 그 다음에 좌 우 이동하는것이 가장 적합. 아래로 간뒤 위로 가는경우는, 마지막에 이동횟수 소진할 때만. 
    while(k--)
    {
        if(x < n && getDist(x + 1, y, r, c) <= k) {answer += "d"; ++x;}
        else if(y > 1 && getDist(x, y - 1, r, c) <= k) {answer += "l"; --y;}
        else if(y < m && getDist(x, y + 1, r, c) <= k) {answer += "r"; ++y;}
        else if(x > 1 && getDist(x - 1, y, r, c) <= k) {answer += "u"; --x;}
    }
    return answer;
}

```

출처 : https://savinglectures123.tistory.com/54

#### 실패한 풀이  - DFS 

```cpp 


#include <string>
#include <vector>
#include <cmath>
using namespace std;

int dy[4] = {1, 0, 0, -1};
int dx[4] = {0, -1, 1, 0};
char dir[4] = {'d', 'l', 'r', 'u'};
string best = "";

int getDistance(int inX, int inY, int inA, int inB) { 
    return abs(inX - inA) + abs(inY - inB);  
}

void DFS(int x, int y, 
         int destX, int destY, 
         int n, int m, 
         int k, int depth, 
         string path) 
{
    if (depth == k) {	
        if (x == destX && y == destY) {
            if (best.empty() || path < best) best = path; // 최소갱신을 하는 로직이지만, 조건에 맞는 최소 루트를 만드는데에는 실패합니다. 
        }
        return; 
    }
    
    for (int d = 0; d < 4; d++) { 
        int newX = x + dx[d];
        int newY = y + dy[d];
        if (newX < 1 || newY < 1 || newX > n || newY > m) continue; 
    
        int dist = getDistance(newX, newY, destX, destY);
        int remain = k - (depth + 1);
        if (dist > remain) continue; 

        DFS(newX, newY, destX, destY, n, m, k, depth+1, path + dir[d]);
    }
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    if (x < 1 || x > n || y < 1 || y > m || r < 1 || r > n || c < 1 || c > m)
        return "impossible";
        
    int TravelLength = getDistance(x, y, r, c); 
    if (TravelLength > k || (k - TravelLength) % 2 != 0)
        return "impossible"; 
         
    best.clear();
    DFS(x, y, r, c, n, m, k, 0, "");
    return best.empty() ? "impossible" : best;
}


```

최소갱신을 위한 best 판별이 제대로 이뤄지지 않아 실패한 풀이입니다. 왜 실패했는지는 로직이 꼬인것으로 추정되어 검토가 필요합니다. 

### DFS 성공한 풀이 

```cpp
 #include <string>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
string answer = "";
string ret = "impossible";
bool flag = false;

int n,m,x,y,r,c,k;
int dx[4] = {1,0,0,-1};
int dy[4] = {0,-1,1,0};
char dir[4] = {'d','l','r','u'};
int get_dist(int x,int y,int a,int b){
    return abs(x-a) + abs(y-b);
}

void dfs(int cnt,int curx,int cury){
    if(!flag){
        
        int dist = get_dist(curx,cury,r,c);
        if(k - cnt - dist < 0) return;
        if((k - cnt - dist) % 2 == 1 ) return;

        if(cnt == k){
            if(curx == r && cury == c){
                flag = true;
                ret = answer;
            }
            return ;
        }
        for(int k = 0 ;k < 4 ;k++){
            int newx = curx + dx[k];
            int newy = cury + dy[k];
            if(newx > 0 && newx <= n && newy > 0 && newy <= m){
                answer += dir[k];
                dfs(cnt + 1, newx, newy);
                answer.pop_back();
            }
        }
    }
}

string solution(int _n, int _m, int _x, int _y, int _r, int _c, int _k) {
    n = _n; m = _m ; x = _x; y = _y; r = _r; c = _c; k= _k;
    dfs(0,x,y);
    return ret;
}
```

출처 - https://allmymight.tistory.com/192


### 유의할점 

DFS는 언제나 그렇듯이 **최소 경로를 보장해주지 않습니다**. 현재와 같이 우선순위가 있고, 조건들이 꽤 많이 걸린 상황이라면 그리디가 더 효율적일 수 있습니다. 

DFS를 사용해야할지, 아니면 그리디 혹은 다른 로직을 사용해야 할 지에대한 판단력으로 난이도를 가르는 문제로, 이 부분에 대해서는 연구가 더 필요합니다. 