
### 최소 신장 트리 

 크루스칼 알고리즘 
 그리디한 방법을 이용 네트워크의 모든 정점을 최소비용으로 연결 하는 알고리즘 입니다. 트리의 최소 비용 전원 탐색을 그리디 적으로 해결하는 방식이라고 보면됩니다,

최소 신장트리를 구하는 알고리즘에느 프리즘 알고리즘과, 크루스칼 알고리즘이 있습니다. 프리즘 알고리즘은 정점을 하나 찍고 인접 정접중 가장 낮은 정점을 계속 방문하며, 크루스칼 알고리즘은 모든 간선을 담고 소팅한뒤에, 가중치가 낮은간선부터 방문 하는 방식입니다. 

#### 프리즘 알고리즘 
- 임의의 정점을 하나 선택해서 최소 신장트리에 추가합니다. 
- 최소 신장트리와 연결되어있는 정점중 가장 가중치가 적은 정점을 최소 신장트리에 추가합니다. 
- 이 것을 최소 신장트리 조건 (모든 노드를 방문하고 순환이 되지 않음)에 맞을때까지 반복합니다. 

프리즘 알고리즘이 유니온 파인드 연산을 쓰지 않는이유. 

> [!NOTE]
> 반면 프림 알고리즘은 시작 정점(start)에서부터 하나의 컴포넌트(C)를 점진적으로 확장해 나가는 방식이에요. 즉, 맨 처음엔 C = {start}, 나머지 정점들은 “포함되지 않은” 상태. 이 “포함되지 않은 정점”들은 모두 격리(isolated) 상태로 봐도 무방하고, 하나씩 C로 들어오면서 MST가 완성됨

문제 출처 : https://www.hackerrank.com/challenges/primsmstsub/problem?isFullScreen=true
```cpp
bool visit[3001]= {false};

struct edge {

    int to, weight;

};

struct node {

    int weight, idx;

    bool operator>(const node &other) const {

        return weight > other.weight; // 최소 힙 로직 

    }

};



vector<edge> adj [3001];

bool visited[3001];

  

int prims(int n, vector<vector<int>> edges, int start) {

	// 인접리스트가 있는지, 없는지는 먼저 인자로 체크 해야함. 
	// 이 문제에서는 edge만 존재하기 때문에, 인접리스트가 없으며, 인접 리스트를 만들어 주어야 함. 
    for (auto& e: edges){

        int u = e[0], v= e[1], w=e[2];

        adj[u].push_back({v,w});

        adj[v].push_back({u,w});

    }
    

    priority_queue<node, vector<node>, greater<node>> pq;

    pq.push({0,start});

    int result = 0;

    int count = 0;
    
    // 그리디로 푸는 정석 프림 코드 우선순위 큐 하나만 사용해도 풀수 있습니다. (BFS와 유사하니 참고.)

    while (!pq.empty() && count < n)

    {
		
        auto [w,u] = pq.top();

        pq.pop();

        if (visited[u])

        {

            continue;

        }

        visited[u] = true;

        result += w;

        count++;

        for (auto &edge : adj[u])

        {

            if (!visited[edge.to])

            {

                pq.push({edge.weight, edge.to});

            }

        }

    }

    return result;

}
```

#### 크루스칼 알고리즘 
- 그래프의 모든 간선을 가중치 기준으로 오름차순 정렬 합니다.
- 가중치가 낮은 간선부터 최소 신장트리에 추가하지만, 순환이 되서는 안됩니다. (유니온 파인드를 사용합니다.)
- 이 과정을 모든 노드를 방문하고 순환이 되지 않을때 까지 반복합니다.

문제 출처 - https://www.hackerrank.com/challenges/kruskalmstrsub/problem?isFullScreen=true
``` cpp
struct info {

    int u, v, wt;

};

// 각 노드의 시작, 도착, 그리고 웨이트를 담습니다. 
  
struct cmp {

  bool operator()(const info &a,const info &b) // 읽기 전용인경우 왠만해서는 const 사용하기. 

  {

    if(a.wt == b.wt) // 가중치가 같은경우.

    {

        return a.u+a.v > b.u+b.v;
        // 우선순위 큐에서 간선을 정렬하기 위한 함수
        // 가중치가 같으면 값이 작은쪽을 우선시. 

    }

    return a.wt > b.wt;  // 가중치가 작은 간선을 우선함. 

  }  

};

// 컴포지션 스트럭트 입니다. 

info Node;

int par[3001]; // 부모 찾기 배열. 

// 순환을 방지하기위한 유니온 파인드 알고리즘입니다. 같은 부모를 가지게 되면 순환하는것으로 칩니다. 

int findRoot(int x)

{

    if (par[x] == x )

    {

        return x;

    }

    return par[x] = findRoot(par[x]);

}

  

void unionroot(int a, int b)

{

    int x = findRoot(a);

    int y = findRoot(b);
    
    // 두 노드를 하나의 집합으로 합치기. 

    if (x < y)

    {

        par[y] = x;

    }

    else if (x > y)

    {

        par [x] = y;

    }

}

// 본격적인 크루스칼 알고리즘 파트입니다. 

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight) {

    // 가중치가 낮은 간선부터 최소신장 트리에 추가 하므로, 우선순위 큐를 사용해서 노드를 저장하면 됩니다. 

    priority_queue<info, vector<info>, cmp> pq;

    // 부모 배열의 초기화, 자기 자신을 부모로 하는 작업.

    for (int i = 1 ; i <= g_nodes; i++)

    {

        par[i] = i; // 중요! 

    }

    int result = 0;

    for (int i = 0; i < g_from.size(); i++)

    {

        Node.u = g_from[i];

        Node.v = g_to[i];

        Node.wt = g_weight[i];

        pq.push(Node); // 간선정보 삽입.

    }

    int count = 0; // 선택된 간선 갯수 

    while(!pq.empty())

    {
		// 노드값 복사하기. 
        int cs = pq.top().u;

        int ce = pq.top().v;

        int cv = pq.top().wt;
		
        pq.pop();
		
		// 같은집합이면 사이클 발생 -> 건너뜀. 
        int ps = findRoot(cs);

        int pe = findRoot(ce);
		
		
		// 같은 집합이면 사이클이 발생 하므로, 건너 뜀. 
        if (ps == pe) continue;
		
		// 서로 다른 집합이면 합치고 간선채택. 
        unionroot (cs,ce);

        result += cv;

        count ++;
		
		// 노드의 수 -1 이 간선. 
        if (count == g_nodes -1) break;

    }

    return result;

}
```

### 이진 트리 


#### 트리 순회 

트리 순회를 하기전에 노드를 선언해야합니다 
```cpp
struct Node{ 
	struct Node* left; 
	struct Node* right;
	
	ELEMENT_TYPE data; // 데이터 형은 자유! 
}
```


트리의 순회 방법은 Pre-order, In-order, 그리고 Post-order가 있으며, 각각의 순회 로직은 왼쪽 혹은 오른쪽이 `nullptr`이 될때까지 진행합니다. 

전위 순회 (pre-order traverse)
```cpp 

void pre_ordertraverse(Node* t)
{ 
	if (t == nullptr)
	{
		return; 
	}
	
	cout << t->data;    // 선출력 
	
	pre_ordertraverse(t->left);  // 왼쪽먼저
	pre_ordertraverse(t->right); // 그리고 오른쪽 
}
```

중위 순회 (in-order traverse)

```cpp
void in_ordertraverse(Node* t)
{
	if (t == nullptr)
	{
		return; 
	}
	
	in_ordertraverse(t->left);
	cout << t->data;
	in_ordertraverse(t->right); 

}

```

후위 순회 (post-order traverse)
```cpp 
void post_ordertraverse(Node* t)
{ 
	if (t = nullptr)
	{
		return; 
	}
	
	post_ordertraverse(t->left);
	post_ordertraverse(t->right);
	cout<< t->date;
}
```