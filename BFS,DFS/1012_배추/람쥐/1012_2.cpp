#include <iostream>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;

// map - we'll use:
// 0: empty cell
// 1: unvisited cabbage
// 2: visited cabbage
int map[50][50];

// Direction arrays for BFS
int dx[4] = {0, 0, -1, 1};  // X directions: no change, no change, west, east
int dy[4] = {-1, 1, 0, 0};  // Y directions: north, south, no change, no change

void bfs(int inX, int inY, int maxX, int maxY)
{
    queue<pair<int, int>> q;
    
    // Mark starting point as visited
    map[inX][inY] = 2;
    q.push({inX, inY});
    
    while (!q.empty())
    {
        pair<int, int> current = q.front();
        q.pop();
        
        int x = current.first;
        int y = current.second;
        
        for (int i = 0; i < 4; i++)
        {
            int nextX = x + dx[i];
            int nextY = y + dy[i];
            
            if (nextX >= 0 && nextY >= 0 && nextX < maxX && nextY < maxY)
            {
                // Check if it's an unvisited cabbage
                if (map[nextX][nextY] == 1)
                {
                    q.push({nextX, nextY});
                    map[nextX][nextY] = 2;  // Mark as visited
                }
            }
        }
    }
}

int CountCabbage(int width, int height)
{
    int cabbageCount = 0;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (map[i][j] == 1)  // If we find an unvisited cabbage
            {
                bfs(i, j, width, height);
                cabbageCount++;
            }
        }
    }
    return cabbageCount;
}

int main()
{
    int c;
    cin >> c;
    
    for (int i = 0; i < c; i++)
    {
        int x, y, p;
        cin >> x >> y >> p;
        
        // Initialize map to zeros
        memset(map, 0, sizeof(map));
        
        // Set cabbage positions
        for (int j = 0; j < p; j++)
        {
            int a, b;
            cin >> a >> b;
            map[a][b] = 1;  // Place a cabbage
        }
        
        cout << CountCabbage(x, y) << endl;
    }
    
    return 0;
}