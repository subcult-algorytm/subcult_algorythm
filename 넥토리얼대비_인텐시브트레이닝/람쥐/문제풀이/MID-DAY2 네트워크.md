
https://school.programmers.co.kr/learn/courses/30/lessons/43162
### 설명 

프로그래머스 DFS/BFS 예제문제에 해당하는 Lvl 3의 문제입니다. **전형적인 탐색 문제로**, 클라 코테의 단골 주제라 할수 있겠습니다. 백준에도 비슷한 문제가 있습니다! 
설명도 프로그래머스 답지 않게 짧고 명확하기 때문에 파악하기 쉽습니다. 
다만, 그룹의 숫자를 물어보기만 하기 때문에, Union-Find로도 충분히 풀이가 가능하나, 조금 더 복잡합니다.

### 키워드 

메인 키워드 
DFS, BFS

서브 키워드 
Union - Find 

### DFS 를 이용한 풀이 

``` cpp 

#include <string>
#include <vector>

using namespace std;

void DFS(int from, int n, vector<int> &visited, vector<vector<int>> &computers) {

    for (int i = 0; i < n; i++) {
        if (from != i && computers[from][i] == 1 && visited[i] == 0) {
            visited[i] = 1;
            DFS(i, n, visited, computers);
        }
    }
}

int solution(int n, vector<vector<int>> computers) {

    int network = 0;
    vector<int> visited(n, 0);

    for (int i = 0; i <n; i++) {
        if (visited[i] == 1) {
            continue;
        }

        // visit node and start DFS
        network++;
        visited[i] = 1;

        DFS(i, n, visited, computers);
    }

    return network;
}



```

출처 - 프로그래머스 풀이. 


### Union - Find 를 이용 한 풀이 

```cpp 

#include <string>
#include <vector>
#include <algorithm>
#include <set>

// UNION FIND SOULTION
using namespace std;

vector<int> parents;


int find (int x)
{ 
    // root node returns itself 
    if (x == parents[x])
    {
        return x; 
    }

    return parents[x] = find(parents[x]); 
    // each node find the node itself. 
}

void union_(int a, int b)
{ 
    a = find (a);
    b = find (b); 

    parents [b] = a; 

}

bool findParent (int a, int b)
{ 
    a = find(a);
    b = find(b); 

    if (a == b) return true; 
    else return false; 
}
int solution(int n, vector<vector<int>> computers) {

    parents.resize(n); 

    // Union find를 사용해서, 두개의 집합을 하나로 합쳐, 연결하고
    // Root를 업데이트 합니다. 

    for (int i = 0 ; i < n; i ++) 
    { 
        parents[i]=i;
    }

    for ( int i  = 0 ; i < n; i ++ )
    {
        for (int j = 0; j < n ; j ++ )
        {
            if (computers[i][j] == 1 && i !=j)
            {
                union_ (i ,j); 
            }

        }
    }

   set<int>networks; 
    for (int i = 0; i < n ; i++)
    { 
        networks.insert(find(i)); 
    }

    return networks.size();

}


```