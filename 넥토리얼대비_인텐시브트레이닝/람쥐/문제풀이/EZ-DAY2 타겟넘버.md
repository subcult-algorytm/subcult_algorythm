https://school.programmers.co.kr/learn/courses/30/lessons/43165
### 설명 

DFS, BFS 문제는, 이딴게 DFS? 같은 문제가 생각외로 많이 나옵니다. 쉽게 플로우따라 순차적으로 움직여서 최적의 방법을 찾는거면 DFS, BFS가 가능하다라고 생각하면 쉽습니다. 
난이도는 최하로, 클라 코테에서도 충분히 1번, 2번 문제로 나올수 있습니다. 


### 키워드 

메인키워드 
이딴게 DFS, BFS

서브키워드 
그리디

### 풀이

언제나 최소거리를 보장하는 BFS로 풀어봅시다. 
처음에는 이딴게 뭐지 싶겠지만, +와 -로 각각 브랜치를하고, n 번째의 Depth에 target과 같은 수가 있는 트리가 어떻게 만들어지는지, 루트부터 탐색한다고 생각하면 매우쉽습니다. 

```cpp

#include <string>
#include <vector>

using namespace std;

 int answer = 0;
void DFS (vector<int> inVector, int depth, int target, int sum)
    { 
        if (depth == inVector.size())
        {
            if (target == sum )
            {
                answer ++; 
            }
        }
        else 
        {
            DFS (inVector, depth + 1 , target, sum + inVector[depth]);
            DFS (inVector, depth + 1 , target, sum - inVector[depth]);
        }
    }

int solution(vector<int> numbers, int target) {


    DFS (numbers, 0, target, 0); 

    return answer;
}
```


### 유의할점 

이딴게 DFS? 같은 소리가 나오는 문제들은 대부분 트리로 플로우를 타서 순회하는 방식이구나라고 생각하면 쉽게 상상이 갑니다. 순회 문제들을 트리 혹은 그래프로 상상하는 습관을 들이면 문제가 쉽게 풀립니다.