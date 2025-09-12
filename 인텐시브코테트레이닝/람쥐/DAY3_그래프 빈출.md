
### Union - Find 
유니온과 파인드는 같이 묶여서 사용 되니 쌍으로 외워야 합니다.
유니온 파인드를 만들기 전, 부모의 목록을 저장하는 컨테이너가 필요합니다. 상황에따라 어레이 혹은 맵을 골라 사용하세요.

사용하기 좋은 경우 : 두개 이상의 그룹이 묶여지는게 확정 적인 경우. 단순 그래프 순회보다 더 효율적, **쿠르스칼 알고리즘, 프리즘 알고리즘** (최소신장 트리문제)

```cpp
/* 
* 1. 부모를 담는 컨테이너 만들기 
* 2. 파인드 함수에서
	* 부모가 인자와 같으면 리턴 
	* 그렇지 않다면 최종 부모를 찾을 때가지 파인드 찾기
* 3. 유니온 함수에서.
	* 두 인자를 가지고 파인드를 실행
	* 두 인자의 부모를 합쳐줍니다.
*/

int Find (int a)
{
	if (a == parents[a])
    {
        return a; 
    }

    return parents[a] = find(parents[a]); // 경로압축 

}

void Union (int a, int b)
{ 
	// 부모 찾기.
    int rootA = find (a);
    int rootB = find (b); 
	
	if ( rootA== rootB)
	{ 
		return 
	}
    parents [rootB] = rootA; 
	
}

// 부모 찾기 - 같은 연결 안에 있는지 확인합니다! 
bool findParent (int a, int b)
{ 
    a = find(a);
    b = find(b); 

    if (a == b) return true; 
    else return false; 
}


```

###  DFS 
 깊이 우선 탐색입니다. 깊이 우선 탐색은 최소거리를 보장하지 않습니다! 다만, 미로 탐색, 미로 제작에서는 BFS보다 우선되어 사용됩니다.

```cpp 
// 스택이 비었는지 확인함 - 스텍이 비었다 > 모든 노드를 방문했음! 
// 스택에서 노드를 pop() -> 팝판 원소는 최근 스텍에 푸시한 노드 
// pop()판 노드의 방문 여부 확인 -
	// 방문 하지 않았다면 방문처리 -> 여기서 이제 방문카운트 ++ 혹은 방문 목록에 푸시! 
	// 방문 했다면 컨티뉴 
// 방문한 노드와 인접한 모든 노드를 확인. 그 중에서 아직 방문하지 않은 노드를 스택에 푸시. 스텍은 역순으로 푸시 합니다. 
int visitedCount = 0; 
void dfs(int start, const vector<vector<int>>& graph)
{ 
	int n = graph.size(); 
	vector<bool> visited (n, false); 
	stack<int> st;
	
	while(!st.empty()){
		
		int node = st.top(); 
		st.pop(); 
		
		// 여기에서 방문기록 내지는 카운트 처리! 
		if (visited[node] != true)
		{
			visited[node] = true; 
			visitedCount ++; 
		}
		for (auto it = graph[node].rbegin(); it != graph[node].rend(); ++it)
		{
			if(!visited[*it])
			{
				st.push(*it);
			}
		}
	}
}

```

### DFS 재귀 
재귀를 사용하는 DFS는 컴포넌트 개수세기, 사이클 감지, 백트레킹에 사용됩니다. Union-Find 로 푸는문제는 재귀로도 푼다고 보면 됩니다. 

```cpp
void dfs (int node, const vector<vector<int>>& graph, vector<bool>& visited)
{
	visited[node] = true; 
	
	for (int next :graph [node])
	{
		if (!visited[next])
		{
			dfs(next,graph, visited); 
		}
	}
}
```

### BFS  - 그래프 
너비 우선 탐색입니다. 너비 우선 탐색은 최소 거리를 보장합니다. 다만 미로 탐색, 미로 제작에서는 편향성 문제가 존재합니다. 
가중치 없는 최단 거리 문제는 모두 BFS로 푼다고 생각하면 됩니다. 

```cpp 

// 큐가 비었는지 확인함 - 큐가 비었다? => 모든 노드를 방문 했음! 
// 큐에서 노드를 pop () - pop() 한 원소는 최근 큐에 푸시한 노드 
// pop() 한 노드의 방문 여부 확인 
	// 방문하지 않았다면 방문 처리 -> 여기서 이제 방문카운트 ++ 혹은 방문목록에 푸시! 
	// 방문 했다면 컨티뉴 
// 방문한 노드와 인접한 모든 노드를 확인. 그 중에서 아직 방문하지 않은 노드를 큐에 푸시, 큐는 선순으로 푸시합니다. 

int visitedCount = 0; 

void bfs(int start, const vector<vector<int>>& graph) 
{
	// 이곳에 그래프 해시 저장. 
	int n = graph.size(); 
	vector<bool> visited(n, false);
	queue<int> q; 
	
	q.push(start); 
	visited[start] = true; 
	
	while(!q.empty())
	{ 
		int node = q.front(); 
		q.pop(); 
		
		// 여기에서 방문 기록 혹은 카운트 처리 하는 공간! 
		for (int next : graph[node]) // 인접 리스트의 경우.
		{
			if (!visited[next])
			{
				q.push(next);
				visited[next] = true;
				visitedCount ++;  
			}
		}
	}
	
}

```

만약 행렬 기반이라고 한다면, 이렇게 인덱스 순회를 사용하는것이 좋습니다. 
```cpp 
for (int i = 0; i < n ; i++)
{ 
    if (!visited[i])
        {
            q.push(i);
           visited[i] = true; 
        }
}
```

### BFS 2차원 격자 맵 - 델타탐색 

```cpp 

int dx[4] = {0 , 1 , -1, 0};
int dy[4] = {-1, 0 , 0, 1};

void BFS (int startX, int startY, const vector<vector<int>>& graph)
{ 
	int n = graph.size(); 
	int m = graph[0].size();
	vector<vector<bool>> visited (n,vector<bool>(m,false)); 
	queue<pair<int,int>> q; 
	
	q.push({startX, startY}); 
	visited[startX][startY] = true; 
	
	while(!q.empty())
	{
		pair<int,int> cur = q.front(); 
		q.pop(); 
		
		int x = cur.first;
		int y = cur.second;
		
		for (int i = 0; i < 4; i++)
		{ 
			int newX = x + dx[i];
			int newY = y + dy[i]; 
			if (newX >= 0 && newX < n && newY >= 0 && newY < m && !visited[newX][newY] ) // 만약 벽판정이 필요하다면,  graph[newX][newY] == 0 or 1. 
			{ 
				q.push({newX,newY}); 
				visited[newX][newY] = true; 
			}
		} 
	}
}

```

델타 탐색시 주의 할 점은, 격자의 바운더리를 확실하게 확정하고 그 것을 벗어나지 않게하기 위한 예외처리를 해야합니다. 

### 뭘 리턴해야할까요? 

그래프 문제는 생각외로 정말 필요한 정보만을 체리피킹해서 구현해야 할 필요가 있습니다. 꼭 필요한 정보만 남기면 의외로 그래프가 다른 알고리즘으로 풀어야 하는 경우도 있습니다. 다만 Test Case에서 걸러질수도 있으니 정석적으로 푸는게 좋은 경우도 있습니다.

## 📌 그래프 탐색 리턴값 선택 가이드

| 문제 유형                   | 적합한 리턴값                                                   | 설명                                |
| ----------------------- | --------------------------------------------------------- | --------------------------------- |
| **연결 요소 개수 / 크기 세기**    | `int visitedCount`                                        | BFS/DFS로 방문한 정점 개수만 필요            |
| **탐색 순서 출력**            | `vector<int>` (그래프), `vector<pair<int,int>>` (격자)         | 방문한 노드의 순서가 필요할 때                 |
| **최단 거리 계산**            | `vector<int> dist` (그래프), `vector<vector<int>> dist` (격자) | BFS의 핵심 활용, 최단 거리 문제 전용           |
| **최단 경로 복원**            | `vector<int> parent`                                      | `dist` + `parent`를 저장해 최종 경로를 재구성 |
| **사이클 판별 / 위상 정렬**      | `bool` (사이클 유무), `vector<int>` (위상 순서)                    | 방문 여부만 확인하거나 위상순서 리턴              |
| **특정 조건 탐색 (예: 미로 탈출)** | `bool` (도착 가능 여부)                                         | 목적지에 도달 가능한지 여부만 중요               |

### 그리디 
그래프는 아니지만, 가끔 순회 문제에서는 그리디가 더 편한 경우도 존재 합니다. 

사용하기 좋은 경우 : 명확한 룰 과 예외처리가 존재한 경우 그리디를 생각해 볼수 있습니다. 반드시 앞에서 선택한 것이 뒤에 영향을 주지 않아야 합니다.