#include <iostream>
#include <vector>

using namespace std;

int dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y, int target) {
    int rows = grid.size(), cols = grid[0].size();
    if (x < 0 || x >= rows || y < 0 || y >= cols)
        return 0;
    if (visited[x][y] || grid[x][y] != target)
        return 0;

    visited[x][y] = true;
    int size = 1;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; ++i) {
        size += dfs(grid, visited, x + dx[i], y + dy[i], target);
    }

    return size;
}

bool hasCluster(vector<vector<int>>& grid, int minSize = 3) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!visited[i][j] && grid[i][j] != 0) {
                int clusterSize = dfs(grid, visited, i, j, grid[i][j]);
                if (clusterSize >= minSize)
                    return true;
            }
        }
    }

    return false;
}

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0, 2},
        {0, 1, 0, 2},
        {3, 3, 3, 2},
        {0, 0, 0, 2}
    };

    cout << (hasCluster(grid) ? "Cluster Found!" : "No Cluster") << endl;
    return 0;
}
