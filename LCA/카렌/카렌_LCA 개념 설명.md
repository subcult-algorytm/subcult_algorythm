```C++
#include <iostream>
#include <vector>
#include <algorithm> // Swap을 사용하기 위해 라이브러리 포함 

std::vector<std::vector<int>> adj; //트리의 연결 관계를 정리하는 adj 
std::vector<int>parent; // 부모를 저장하는 vector 
std::vector<int>depth; // 깊이를 저장하는 vector
std::vector<bool> visited; //방문 여부를 저장하는 vector  

/*

LCA는 최소 공통 조상을 찾기 위해 

두가지 정보가 필요한데, 부모 parent와 depth 정보이다.

각 노드를 한번 씩 방문하면서 parent와 depth 정보를 얻기위해 dfs가 필요하다.

*/
void dfs(int u, int p, int d) // u는 현재 방문 하고 있는 노드의 번호, p는 u의 부모노드 , d는 u의 깊이  
{
    visited[u] = true; 
    parent[u] = p;
    depth[u] = d;

    for (int v : adj[u]) // adj[u]의 값을 v에 넣어서 넣을 원소가 없을때까지 반복.  
    {
        if(!visited[v])
        {
            dfs(v,u,d+1);
        }
    }
}

/*

LCA 단계는 핵심적으로 두 단계로 이루어져 있다.

1. 높이 맞추기 

더 깊이 있는 노드를 부모 방향으로 한칸 씩 올려보내서 두 노드의 depth를 똑같이 맞춰준다.

2. 함께 올라가기 

높이가 같아졌다면 두 노드를 동시에 부모 방향으로 한 칸씩 올려 보낸다. 

*/
int lca(int u,int v)
{
    if(depth[u]<depth[v]) // 만약 depth[v]가 u 보다 작으면 아래 행동을 실행 
    {
        std::swap(u,v); // 서로의 depth값을 바꿔주는  작업을 해서 depth[u]가 depth[v]보다 큰것이 보장  
    }

    while(depth[u] != depth[v])
    {
        u = parent[u]; // depth[u]가 depth[v]랑 같아질때까지 위로 올라감  
    }

    while(u!=v) // 깊이가 같아진 이후, 부모값이 같아 질때 까지 반복.  
    {
        u = parent[u];
        v = parent[v];
    }
    return u;
}

int main()
{
    // 예시 코드 이므로 n을 7로 고정해서 설명한다. 

    int n = 7;

    adj.resize(n+1);
    parent.resize(n+1);
    depth.resize(n+1);
    visited.resize(n+1,false);

    /*

    resize 함수를 이용해서 크기를 8로 만들어줌.

    7 + 1

    */

    std::vector<std::pair<int,int>> edges = {{1,2},{1,3},{2,4},{2,5},{3,6},{3,7}}; // 트리 생성 

    for(const auto& edge : edges)
    {
        int u = edge.first; // edge의 첫번째 원소를 u에 담는다 
        int v = edge.second; // edge의 두번째 원소를 v에 담는다 
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1,0,0);

    int node1 = 3;
    int node2 = 4;
    int result = lca(node1,node2);
    std::cout << node1 << "번 노드와 " << node2 << "번 노드의 LCA는 " << result << "번 노드입니다.\n";

    return 0;
}
```

### 필요한 라이브러리

algorithm라이브러리는는
swap을 사용하기 위해서 포함시켜준다.

### main 함수 흐름

1\. 트리 연결관계 만들기

2\. DFS를 이용해서 정보 수집

3\. LCA 실행 및 결과값 출력

### Resize 함수

```C++
int n = 7;

adj.resize(n+1);
parent.resize(n+1);
depth.resize(n+1);
visited.resize(n+1,false);​
```

vector의 크기를 강제로 늘려주는 함수이다.

채워지는 값은 기본 값으로 채워지는데 어떤 type이냐에 따라 달라진다.

(만약,int일 경우 0)

이 포스팅에서 크기를 늘릴때 사용 했지만 줄일때도 사용 할 수 있다.

### 자료구조 Pair

두개의 값을 하나로 묶어서 관리해 주는 자료구조

일단 pair라고 명시적으로 표기함으로서 가독성이 좋아진다.

### _Bounus : 변수에 값을 넣어주는 여러가지 방법_

#### 현재 코드에 나와 있는 방법

```C++
for(const auto& edge : edges)
{
int u = edge.first; 
int v = edge.second; 
adj[u].push_back(v);
adj[v].push_back(u);
}
```

#### C++11 이상에서 사용 할 수 있는 방법

```C++
for (const auto& edge : edges) 
{
    int u, v; 
    std::tie(u, v) = edge;
    adj[u].push_back(v);
    adj[v].push_back(u);
}
```

tie를 이용해서 두줄이였던 코드가 한줄로 줄어들었으나,

변수를 for문을 사용하기 이전에 선언을 해야 한다는 단점이 존재한다.

std::tie 는 미리 준비해둔 변수에 값을 넣어주는 함수이기 때문이다.

#### C++17 이상에서 사용 할 수 있는 방법

```C++

for (const auto& [u, v] : edges)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}
```

변수를 미리 선언해 주지 않아도 되고 코드도 가장 간결하다.