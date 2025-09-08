
### Union - Find 
유니온과 파인드는 같이 묶여서 사용 되니 쌍으로 외워야 합니다.
유니온 파인드를 만들기 전, 부모의 목록을 저장하는 컨테이너가 필요합니다. 상황에따라 어레이 혹은 맵을 골라 사용하세요.

사용하기 좋은 경우 : 두개 이상의 그룹이 묶여지는게 확정 적인 경우. 단순 그래프 순회보다 더 효율적. 

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

void Find (int a)
{
	if (a == parents[a])
    {
        return a; 
    }

    return parents[a] = find(parents[a]); 

}

void Union (int a, int b)
{ 
    a = find (a);
    b = find (b); 

    parents [b] = a; 
	
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

### BFS 
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
		for (int next : graph[node])
		{
			if (!visited[next])
			{
				q.push(next);
				visited[next] = true; 
			}
		}
	}
	
}



```


### 뭘 리턴해야할까요? 

그래프 문제는 생각외로 정말 필요한 정보만을 체리피킹해서 구현해야 할 필요가 있습니다. 꼭 필요한 정보만 남기면 의외로 그래프가 다른 알고리즘으로 풀어야 하는 경우도 있습니다. 다만 Test Case에서 걸러질수도 있으니 정석적으로 푸는게 좋은 경우도 있습니다.

###
### 그리디 
그래프는 아니지만, 가끔 순회 문제에서는 그리디가 더 편한 경우도 존재 합니다.

사용하기 좋은 경우 : 명확한 룰 과 예외처리가 존재한 경우 그리디를 생각해 볼수 있습니다. 