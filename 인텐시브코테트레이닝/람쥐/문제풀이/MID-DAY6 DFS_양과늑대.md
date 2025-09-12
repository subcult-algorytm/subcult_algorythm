
### 개요
너무 전형적이고 전통적인 트리 순회 DFS 문제입니다. Lvl 3으로 책정되었으나, lvl 2정도의 난이도입니다. 양과 늑대관련해서 예외처리만 간단히 해주면 되기 때문에, 어려운것이 하나도 없습니다. 정답률이 33%라고 하는데 아마 코테의 심리적 환경문제가 컸을거라 생각합니다. 권장 시간복잡도도 O^2로 매우 넉넉합니다. 전통적인 문제는 전통적인 방법으로 풉시다.

주의 할 점은, **어느 순간에도 늑대수가 양 이상이 되어서는 안됩니다**. 지문을 자세히 읽으면 늑대의 숫자가 양보다 적은경우, 늑대는 따라와서 양을 잡아먹지 않지만, 같은 숫자인 경우 늑대가 양을 모두 잡아 먹게되고, 앞으로의 탐방에서도 늑대 > 양 숫자가 되므로, 애초에 양이 모일수있는 전제가 성립되지 않습니다. 이 부분은 지문을 읽어서 나오는 부분이나, 프로그래머스 답게, 명확하게 명시되지 않고 맥락상 짚어야하는 부분이므로, 이 부분 역시 낮은 정답률에 한 몫했을거라고 생각됩니다.

### 풀이 
DFS 내부에 양과 늑대의 숫자를 카운트 하는 로직을 지정하고, 해당 루트를 방문할 때, 늑대의 수가 양의 숫자보다 같거나 더 많을경우엔 카운트 자체를 하지 않는 식으로 예외처리 하는것을 빼면 전형적인 DFS 구현입니다. 

```cpp 

vector<vector<int>> tree; // 트리 
vector<int> visited, comp; //
int n, answer = 0; 

```

늑대와 양을 카운트 하느 로직을 DFS 순회 전에 써야합니다. 
```cpp 
void DFS(vector<int> cur)
{ 
	int sheep = 0; int wolf = 0; // 양과 늑대 숫자를 카운트 하는 로직입니다. 
	for (int c : cur)
	{
		if (comp [c] == 1)  // 노드가 1이면 늑대이니 늑대를 카운트 합니다. 
		{
			wolf ++;  
		}
		else 
		{ 
			sheep ++; // 0 이면 양을 카운트 합니다. 
		}
	
	}
	
	if (wolf >= sheep) 
	{
		return;  // 늑대
	}
	answer = max(answer, sheep); // sheep 카운트와 answer 중에 큰걸 리턴하는 방식입니다. 

```

그 뒤는 전형적인 DFS 순회입니다(?)
```cpp 
for (int i = 0 ; i < cur.size(); i ++ )
{
	int node = cur[i]; // 이번 문제는 배열을 사용하는걸 알 수 있습니다. 
	for (int g : tree[node])
	{
		if (visited[g])
		{ 
			continue;
		}
		visited[g] = true; 
		cur.push_back(g);
		DFS(cur); // DFS 순회 방식입니다. 
		cur.pop_back(); // 순회뒤에는 pop_back 합시다. 
		visited[g] = false; 
	} 
}
```

솔루션 함수에서는 Info 와 엣지 정보를 바탕으로, 트리와 방문기록의 크기를 재조정하고, 인접리스트를 작성해서 초기화 하며, 그 후 DFS를 순환합니다. 여기서 DFS는 컨테이너를 인자로 받기 때문에 첫 노드를 인자로 던져 줍시다. 인접리스트는 바깥에서 전역으로 처리합니다. (어자피 그래프는 1개이므로..)
```cpp
int solution(vector<int>info, vector<vector<int>> edges){
	n = info.size(); 
	tree.resize(n); 
	
	visited.resize(n, false); 
	comp = info; 
	
	for (auto e : edges)
	{
		tree[e[0]].push_back(e[1]);  // 인접리스트를 작성. 
	}
	visited[0] = true; 
	// 여기 까지는 초기화 과정입니다. 트리와 방문기록을 초기화하고, 인접리스트를 작성합니다. 
	
	DFS({0}); // DFS 순환의 시작입니다. 
	return answer; 
}
```


> [!NOTE] 인접리스트를 인자로 잡는것과 안잡는것의 차이는??
> 인접리스트를 인자로 잡아서 순회로 쓰게되면, 재사용성이 높고, 여러개의 그래프를 동시에 다를수있지만, 그래프를 매일 넘겨줘야 하며, 바깥에 두어 전역변수화 해서 사용하면 구현이 편해지긴하나 전역변수된 인접 리스트에 의존해야합니다. 
> 대부분의 **코테 문제의 순회는 그래프를 1개만 사용하므로**, 전역변수화 하는쪽이 조금 더 편한 편이나, 실사용에서는 인자로 넘겨줘야 하는 때가 종종 있습니다. 



### 다른 풀이 - 비트마스크 연산을 통한, 늑대/양 구분. 
공간복잡도가 꽤 크게 나오기 때문에 늑대/양을 구분하는 부분에서 공간을 축소 시키지 않으면 공간복잡도의 문제로 시간초과가 나오게 됩니다. 이 부분이 정답률을 낮추는 원인으로 작용했을거라 생각합니다. 

만약 DFS를 정석으로 쓰고 싶다면, 비트마스크 연산을 통해서, 늑대가 양보다 많으면 제거하고, 중복역시 제거함으로써, 공간은 여전히 2^n 이지만 공간의 양 자체를 확 줄일수 있습니다. 
특이한점은 comp 에다 늑대와 양의 연산을 DFS의 인자로써 받아서 한다는 것이고, 실시간으로 양/늑대의 현재 숫자를 받게 되므로, 늑대 >= 양이 되는 시점에 바로 조기리턴 함으로써 탐방 숫자를 확 줄일수있습니다. 

```cpp 
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> tree;
vector<int> comp; // 0 = sheep, 1 = wolf
int answer = 0;

void DFS(int mask, int sheep, int wolf) {
    // 늑대가 양 이상이면 실패
    if (wolf >= sheep) return;

    // 최대 양 수 갱신
    answer = max(answer, sheep);

    // mask에 포함된 노드들 중, 자식으로 확장
    for (int i = 0; i < comp.size(); i++) {
        if (!(mask & (1 << i))) continue; // 포함된 노드가 아니면 skip
        for (int nxt : tree[i]) {
            if (mask & (1 << nxt)) continue; // 이미 방문한 노드면 skip
            int nxtMask = mask | (1 << nxt);
            DFS(nxtMask, sheep + (comp[nxt] == 0), wolf + (comp[nxt] == 1));
        }
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    int n = info.size();
    tree.assign(n, {});
    comp = info;

    for (auto &e : edges) {
        tree[e[0]].push_back(e[1]);
    }

    // 시작 상태: 루트(0번)
    DFS(1, comp[0] == 0 ? 1 : 0, comp[0] == 1 ? 1 : 0);
    return answer;
}

```

비트마스크의 연산방식을 따로 가져와 봅시다.

```cpp

// mask에 포함된 노드들 중, 자식으로 확장
    for (int i = 0; i < comp.size(); i++) {
        if (!(mask & (1 << i))) continue; // 포함된 노드가 아니면 skip
        for (int nxt : tree[i]) {
            if (mask & (1 << nxt)) continue; // 이미 방문한 노드면 skip
            int nxtMask = mask | (1 << nxt);
            DFS(nxtMask, sheep + (comp[nxt] == 0), wolf + (comp[nxt] == 1));
        }
    }
    
```

일단 mask는 정수 (int)로, 이진수로 봤을 때, 각 비트가 특정노드를 방문했는지 여부를 기록합니다. 
노드가 5개인경우 
`mask = 00101` 이 있다면, 0번과 2번 노드를 방문했다는 뜻으로, 1이 켜진 곳은 노드 방문이 완료되었다 보면 됩니다. 

즉, `(mask & (1 << i))`  는 i 번 노드를 방문했는지 확인하는 연산이고. 
` mask | (1 << nxt)` 는 nxt 번 노드를 방문했다고 표시하는 연산입니다. 

| 는 비트마스크의 or 연산으로써, 이전의 mask와 i 위치를 대조, 1이 있는곳을 대입합니다.

예를 들어, 
`mask | (1 << 1)` 에서는 `0001` 와 `0010`을 OR 연산하게 되며 결과는 `0011` 이 됩니다.

그리고 이렇게 만든 2진수를 nxtMask에 저장해, 양 숫자와, 늑대숫자와 함께 순회합니다. 


### 주의할점 
O^2으로 넉넉하게 시간/공간 복잡도를 주는거 같지만, 제한시간이 빡빡해, 모든 케이스를 탐방해서는 안됩니다. 이런 경우 조기 리턴할수있는 예외처리를 꼭 해주는것이 중요합니다. 

이 문제와같이 조기 리턴 해야하는 조건이 명확한경우, 이 경우를 완전히 배제하는 예외처리를 가장 먼저 해주어 탐방 시간을 줄이는게 관건입니다. 