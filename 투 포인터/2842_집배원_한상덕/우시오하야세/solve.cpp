#include <bits/stdc++.h>

#define FAST_IO                   \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);

using namespace std;

int N;
set<int, less<int>> heights;
pair<int, char>* da;
pair<int, char>** arr;
int P;
pair<int, int> p_coor;
int K_cnt = 0;
bool* visited_da;
bool** visited;
int drow[8] = {1, 0, -1, 0, 1, 1, -1, -1};
int dcol[8] = {0, 1, 0, -1, 1, -1, 1, -1};

bool bfs(int min_v, int max_v)
{
    if (P < min_v || P > max_v) return false;
    memset(visited_da, false, N * N * sizeof(bool));
    int K = 0;
    queue<pair<int, int>> q;
    q.push(p_coor);

    while (!q.empty())
    {
        pair<int, int> coor = q.front();
        if (arr[coor.first][coor.second].second == 'K') ++K;
        q.pop();

        for (int i = 0; i < 8; ++i)
        {
            int new_row = coor.first + drow[i];
            int new_col = coor.second + dcol[i];

            if (new_row >= 0 && new_row < N && new_col >= 0 && new_col < N && !visited[new_row][new_col] &&
                arr[new_row][new_col].first >= min_v && arr[new_row][new_col].first <= max_v)
            {
                q.emplace(new_row, new_col);
                visited[new_row][new_col] = true;
            }
        }
    }

    if (K == K_cnt) return true;

    return false;
}

int main()
{
    FAST_IO;
    cin >> N;

    da = new pair<int, char>[N * N];
    arr = new pair<int, char>*[N];
    visited_da = new bool[N * N];
    visited = new bool*[N];

    for (int i = 0; i < N; ++i)
    {
        arr[i] = da + i * N;
        visited[i] = visited_da + i * N;

        for (int j = 0; j < N; ++j)
        {
            char c;
            cin >> c;
            arr[i][j].second = c;

            if (c == 'K')
                ++K_cnt;
            else if (c == 'P')
                p_coor = {i, j};
        }
    }

    for (int i = 0; i < N * N; ++i)
    {
        int x;
        cin >> x;
        da[i].first = x;
        heights.insert(x);
    }

    P = arr[p_coor.first][p_coor.second].first;

    vector<int> sorted_da(heights.begin(), heights.end());

    int left = 0, right = 1;
    int result = 0x7fffffff;

    while (right < sorted_da.size())
    {
        int diff = sorted_da[right] - sorted_da[left];

        if (bfs(sorted_da[left], sorted_da[right]))
        {
            result = min(result, diff);
            ++left;
        }
        else
        {
            ++right;
        }
    }
    cout << (result == 0x7fffffff ? 0 : result);
}
