
**프로그래머스 - 게임맵 최단거리**

### 개요

매우 전형적인 DFS, BFS 문제입니다. 아주 쉬운문제로, 초반 1,2번에 나올 가능성이 높습니다. 클라 단골 메뉴이기도 하지만 실제 구현에서도 자주 쓰이는 알고리즘이기 때문에 외우는게 좋습니다. 

### 풀이

최단 거리문제의 풀이는 이렇게 흘러갑니다 

- 최단 거리를 구할수 있는 알고리즘을 구한다. 
- 최단 거리를 구하는 알고리즘에 시작점을 넣는다. 
- 그 뒤, 조건에 맞을때 까지 순회하는 로직을 넣는다.
- 조건에 맞으면 멈추고 문제에서 요구하는 값을 프린트 한다. 

주의 할 점은 
- 만약 배열 자체를 가져와야 하는경우, `Call by Reference`로 참조를 불러오는것이 속도 면에서 좋습니다. 
```cpp

void BFS (int a, int b, vector<vector<int>>& inMap)
```

- 배열의 최대치, 예외처리에 주의 하지 않으면 Segment Fault등의 잘못된 접근 오류가 나니 주의합니다. 
```cpp
  if (maps[0][0] == 0 || maps[maxX-1][maxY-1] == 0)
    {
        return -1;
    }
    
    // maxX에 -1을 하지 않아 Segmenet falut 문제가 생겨버림. 

```

- 만약 문제가 생겼다면 열의 아홉은 잘못된 인덱스 접근일 가능성이 높다. 

- 알고리즘 자체는 탬플릿 화 해서 가져다 쓰는게 편하다. 

``` cpp

#include<vector>
#include<queue>
using namespace std;


int startX = 0;
int startY = 0; 

int maxX = 0; 
int maxY = 0; 

int dy [4] =  { 1, 0 , 0 , -1}; 
int dx [4] =  { 0, -1, 1, 0};

int answer = 0;


void BFS (int a, int b, vector<vector<int>>& inMap)
{ 

    vector<vector<bool>> visited(maxX, vector<bool>(maxY, false));
    queue<pair<pair<int,int>,int>>q; 

    q.push ({{a,b}, 1}); 
    visited [a][b] = true; 

    while (!q.empty()){
        auto cur = q.front(); 
        q.pop(); 

        int x = cur.first.first;
        int y= cur.first.second;
        int dist = cur.second; 

        if (x == maxX -1 && y == maxY -1 )
        {
            answer = dist; 
            return;
        }

    for (int d = 0 ; d < 4 ; d++)
        {
            int newX = x + dx[d];
            int newY = y + dy[d]; 
            if (0 <= newX && newX < maxX 
               && 0<= newY && newY < maxY 
                && !visited[newX][newY] && inMap[newX][newY] == 1 )
            {
                visited [newX][newY] = 1 ; 
                q.push({{newX,newY} , dist +1});
            }
        }
    }
    answer = -1; 
}

int solution(vector<vector<int>> maps)
{

    // get the row and column of the maps and store it to the maxX and maxY 

    // Column size maxX = n
    // Row Size maxY = m
    maxX = maps.size();      // this will be n
    maxY = maps[0].size();   // this will be m 


    // Starting and Ending point isn't vaild. 
    if (maps[0][0] == 0 || maps[maxX-1][maxY-1] == 0)
    {
        return -1;
    }

    BFS(0,0, maps); 

    return answer; 

}

```


### maps 에 직접 넣기 

```cpp


#include<vector>
#include<iostream>
#include<queue>

using namespace std;

int check[101][101];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int solution(vector<vector<int> > maps)
{
    int n, m;
    n = maps.size();
    m = maps[0].size();
    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));
    check[0][0] = true;

    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for(int i=0; i<4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(0<=nx && nx<n && 0<=ny && ny<m){
                if(check[nx][ny] == false && maps[nx][ny] > 0){
                    check[nx][ny] = true;
                    maps[nx][ny] = maps[x][y] + 1;
                    q.push(make_pair(nx, ny));
                }
            }
        }
    }



    int answer = 0;
    if(maps[n-1][m-1] == 1){
        answer = -1;
    }else{
        answer = maps[n-1][m-1];
    }
    return answer;
}



```

출처 - 프로그래머스 
### 포인터를 사용해 각 노드를 객체화한 풀이 

코테에서는 효과적인 풀이는 아니지만,  각 노드를 객체화 하는 방법은 실제 구현에서는 유용하기때문에 참고하면 좋습니다. 

```cpp 

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    int row, col;
    int gCost, hCost, fCost;

    bool isClosed;
    bool inOpenList;
    int isPath;

    Node* parentNode;

    Node() :
    gCost(0), hCost(0), fCost(0), isClosed(false), inOpenList(false), parentNode(nullptr)
    {}
};

Node* startNode, *endNode;
priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> openList;
int dir[4][2] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0}};



bool inBound(int x, int y, int row, int col)
{
    return x >= 0 && x < row && y >= 0 && y < col;
}

void reversePath(Node* first, Node* next, int* step)
{ 
    if (next != nullptr)
    {
        (*step)++;
        reversePath(next, next->parentNode, step);
        next->parentNode = first;
    }
}

int solution(vector<vector<int> > maps)
{
    int answer = 0;

    int col = maps[0].size();
    int row = maps.size();

    Node myMaps[row][col];

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            myMaps[i][j].row = i;
            myMaps[i][j].col = j;
            myMaps[i][j].isPath = maps[i][j];
        }
    }

    startNode = &myMaps[0][0];
    endNode = &myMaps[row - 1][col - 1];


    //FindPath
    Node* tempNode = startNode;

    while (tempNode != endNode)
    {
        int idRow = tempNode->row;
        int idCol = tempNode->col;
        int count = 0;

        Node* openTempNode;
        tempNode->isClosed = true;

        for (int i = 0; i < 4; i++)
        {                
            if (inBound(idRow + dir[i][0], idCol + dir[i][1], row, col))
            {
                openTempNode = &myMaps[idRow + dir[i][0]][idCol + dir[i][1]];
                if (openTempNode->isPath == 0) continue;

                if (openTempNode->isClosed == false)
                {
                    if (openTempNode->inOpenList == true)
                    {  
                        if (tempNode->gCost < openTempNode->gCost)
                        {
                            openTempNode->parentNode = tempNode;
                            openTempNode->gCost = tempNode->gCost + 1;
                            openTempNode->fCost = openTempNode->gCost + openTempNode->hCost;
                        }
                    }
                    else
                    {    
                        int dr = endNode->row - openTempNode->row;
                        int dc = endNode->col - openTempNode->col;

                        openTempNode->gCost = tempNode->gCost + 1;
                        openTempNode->hCost = dc + dr;
                        openTempNode->fCost = openTempNode->gCost + openTempNode->hCost;

                        openTempNode->inOpenList = true;
                        openTempNode->parentNode = tempNode;

                        openList.push(pair<int, Node*>(openTempNode->fCost, openTempNode));      
                    }
                }
            }
        }
        while (true)
        {
            if (openList.size() < 1)
                    return -1;
            if ( openList.top().second->isClosed == true)
            {
                openList.pop();
                continue;
            }
            else
            {
                tempNode = openList.top().second;
                break;
            }
        }
    }

    reversePath(nullptr, endNode, &answer);

    return answer;
}

```

출처 - 프로그래머스 

### 유의할점 

BFS/DFS 구현 방법은 그냥 탬플릿 화 해서 가져다 쓰거나 외우는게 좋습니다. 클라이언트 업무및 코테에서 단골 알고리즘으로, BFS/DFS는 꼭 외워서 칠수 있을정도로 단련 해야합니다. 