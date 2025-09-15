
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std; 

int map [1000][1000];
int TomatoIndex [1000][1000];
queue<pair<int,int>> q;

int ans = 0; 

int dx[4] = { 0, 0, -1, 1};
int dy[4] = { -1, 1, 0, 0}; // N S W E

int width, height; 
// Tomato problem - BFS version.

void bfs (int maxX, int maxY)
{
    while (!q.empty())
    {
        pair <int, int> current = q.front();
        q.pop();
        
        for (int i = 0; i < 4 ; i ++)
        {
            int nextX = dx[i] + current.first;
            int nextY = dy[i] + current.second;
            
            if (nextX >= 0 && nextY >= 0 && nextX < maxX && nextY < maxY)
            {
                if (TomatoIndex[nextX][nextY] == 0)
                {
                    TomatoIndex [nextX][nextY] = TomatoIndex[current.first][current.second] + 1;
                    q.push({nextX, nextY});
                }
                
            }
        }
    }
}

int StatusTomoato(int width, int height)
{
    for (int i = 0; i < width; i ++)
    {
        for (int j = 0; j < height; j ++)
        {
            if (TomatoIndex [i][j] == 0)
            {
                cout << -1 ; 
               return 0; 
            }
            else if (ans < TomatoIndex[i][j])
            {
                ans = TomatoIndex[i][j]; 
            }
        }
    }
    cout << ans -1 ; // get the trash value 
}

int main(int argc, char* argv[])
{
    cin >> width >> height; // input the width and height of the map 1. 
 
    for (int i = 0 ; i < width ; i ++ )
    {
        for (int j = 0; j < height ; j++ )
        {
            cin >> map[i][j]; // input the status of the tomato 
            if (map [i][j] == 1) q.push({i, j}); // start point of bfs;
        }
    }
    bfs(width, height);
    StatusTomoato(width, height);
    
    return 0 ; 
}
