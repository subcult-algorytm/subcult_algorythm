
### 개요 
BFS 클래스를 구성해야하지만 엣지의 시작지점, 끝지점, 그리고 엣지 컨테이너까지 순수한 bfs 순회 클래스가 아닌 엣지 정보, 그래프 정보까지 담아야하는군요. 
게다가 유니온 파인드로 풀어야하는데라는 본능이 있는 사람들을 견제하기 위해서인지, BFS로 고정했군요. 원통하고 원통합니다.


### 풀이 

- 기본적으로 무방향 그래프며 가중치가 없습니다. 
- 다만, 문제에서는 가중치 고정값을 6으로 둡니다. 
- 시작 노드에서 다른 모드노드까지 최단거리를 6의 배수로 출력합니다.
- 갈수없는 노드는 -1로 예외 처리 합니다. 


인접리스트가 필요한 문제고, 거리를 배열로 프린트 해야하므로, 인접리스트 생성부터 합시다. 
배열에 저장할수도 있고, 해쉬테이블로도 저장가능하나, 배열로 저장하는것이 간단하고 빠릅니다. 

```cpp 

vector <vector<int>> graph(n+1); 

for (auto &e: edges)
{ 
	int u = e[0], v= e[1];
	graph[u].push_back(v);
	graph[v].push_back(u); // 양방향 그래프이므로 반대편도 이어줘야 합니다. 
}

```

거리 배열은 1인덱스이므로, 크기를 n+1 해야 세그멘트 오류가 나지 않습니다. 대부분의 세그멘테이션 오류는 이런 배열의 잘못된 접근 때문입니다. 그리고 모든 값을 -1로 초기화 합시다


본격적인 BFS 로직입니다. 거의 비슷하나, 거리를 측정해야한다는점, 그것을 기반으로 6의 배수의 거리를 계산해야합니다.

```cpp

while (!q.empty())
{
	int node = q.front();
	q.pop();
	
	for(int next : graph[node])
	{ 
		if(dist[next] == -1)
		{ 
			dist[next] = dist[node] + 6;
			q.push(next);
		}
	} 
}

```


계산된값은 큐에 넣어져야 하며, 자신을 제외한 모든 노드의 거리를 출력합시다. 여기서 탐색 로직이 시작됩니다. 

```cpp 
vector <int> result; 
for (int i = 1; i <= n; i++)
{ 
if (i != s ) result.push_back(dist[i]);
}
return result; 
```


그리고 리스트를 출력하면 끝입니다.


```cpp 

vector<int> bfs(int n, int m, vector<vector<int>> edges, int s) {

    vector<int> compLength(n, 0);

    // make the adjusted list!

    vector<vector<int>> graph(n +1 );

    for (auto &e: edges )

    {

        int u = e[0];

        int v = e[1];

        graph[u].push_back(v);

        graph[v].push_back(u);

    }

    vector <int> dist(n+1, -1);

    queue <int> q;

    dist[s] = 0;

    q.push(s);

    while (!q.empty())

    {

        int node = q.front();

        q.pop();

        for (int next : graph[node])

        {

            if (dist[next] == -1)

            {

                dist[next] = dist[node] + 6;

                q.push(next);

            }

        }

    }

       vector<int> result;

        for(int i =1; i<= n; i ++)

        {

            if (i != s)

            {result.push_back(dist[i]);}

        }

    return result;

}
```

### 주의 할점

그리 어려운건 없지만, 간접리스트를 만들때 인덱스를 햇갈리면 안된다는 점, 그리고 간선 가중치를 반영행하는 점을 빼면 쉽습니다. 