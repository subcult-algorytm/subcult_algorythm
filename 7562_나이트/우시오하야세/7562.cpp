#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int t, l;

int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

int map[300][300];
int check[300][300];
int visited[300][300];
queue<pair<int, int>> q;

void BFS(int target_x, int target_y)
{
    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        visited[x][y] = 1;
        q.pop();
        if (x == target_x && y == target_y)
        {
            cout << check[x][y] << '\n';
            return;
        }

        for (int i = 0; i < 8; i++)
        {
            int next_x = x + dx[i];
            int next_y = y + dy[i];

            if (next_x >= 0 && next_x < l && next_y >= 0 && next_y < l && visited[next_x][next_y] == 0)
            {
                visited[next_x][next_y] = 1;
                check[next_x][next_y] = check[x][y] + 1;
                q.push({next_x, next_y});
            }
        }
    }
}

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> l;
        int night_x, night_y;
        int target_x, target_y;
        cin >> night_x >> night_y;
        cin >> target_x >> target_y;

        q.push({night_x, night_y});
        BFS(target_x, target_y);

        for (int i = 0; i < 300; i++)
        {
            for (int j = 0; j < 300; j++)
            {
                check[i][j] = 0;
                visited[i][j] = 0;
            }
        }
        while (!q.empty())
            q.pop();
    }
}