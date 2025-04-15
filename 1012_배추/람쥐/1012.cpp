
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;

// 1. find the carabage throguh the map
// 2. if find the carabage, start the travel to nearby carbage
// 3. if there is no carbarge to travel, start to find the carabage again
// 4. Repeat the step 2 and 3 until all carabage is founded. 

// map
int map [50][50];
bool visited[50][50] = {false}; // ?? 
// visited
queue<pair<int,int>> q;
int c;

//
int dx[4] = { 0, 0, -1, 1}; 
int dy[4] = { -1, 1, 0, 0}; // N S W E  
void bfs(int inX, int inY, int maxX, int maxY )
{
    visited[inX][inY] = true;
    q.push({inX,inY});
    
    while (!q.empty())
    {
        pair <int, int> current = q.front();
        q.pop();

        int x = current.first;
        int y = current.second;

        for (int i = 0 ; i < 4 ; i ++ )
        {
            int nextX = x + dx[i];
            int nextY = y + dy[i];

            if (nextX >= 0 && nextY >=0 && nextX < maxX && nextY < maxY)
            {
                if (map[nextX][nextY] == 1 && visited[nextX][nextY] == false)
                {
                    q.push({nextX, nextY});
                    visited[nextX][nextY] = true;
                }
            }
        }
    }
}

int CountCabbage (int width, int height)
{
    int CabbageCount = 0;
    for (int i = 0 ; i < width ; i ++)
    {
        for (int j = 0 ; j < height ; j ++)
        {
            if (map[i][j] == 1 && visited[i][j] == false)
            {
                bfs(i,j,width,height);
                CabbageCount++;
            }
        }
    }
    return CabbageCount;
}

int main ()
{
    cin >> c;
    int x, y, p;
    for (int i = 0; i < c; i++)
    {
        cin >> x >> y >> p;
        memset(map, 0, sizeof(map));
        memset(visited, false, sizeof(visited));
        for (int j = 0; j < p; j++)
        {
            int a, b;
            cin >> a >> b;
            map[a][b] = 1;
            // have to set the start point
        }
       
        cout<<CountCabbage(x,y)<<endl;
    }
    
    return 0; 
}