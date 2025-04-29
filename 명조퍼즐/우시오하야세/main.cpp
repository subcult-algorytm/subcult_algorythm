#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

/**
 * 중간 저장
 */

struct Colors
{
    set<int> R;
    set<int> G;
    set<int> B;
    set<int> Y;
};

int N, M, T;
char target;

char arr[10][10];                 // 각 칸의 색깔
int nodeNum[10][10];              // 각 노드의 집합 번호
vector<pair<int, char>> sets(1);  // 각 집합의 부모 집합 (Union-Find 사용 예정)
vector<int> blockCnt(1);          // 각 집합의 블록 수
Colors colors;                    // 나중에 같은 색깔에 있는지 확인할 트리

int dx[4]{1, -1, 0, 0};  // dx로 쓴건 습관
int dy[4]{0, 0, 1, -1};

/// @brief 집합별 분류
/// @param row 행
/// @param col 열
/// @param currId 현재 집합 번호
/// @param beforeColor 현재 탐색 중인 색깔
/// @param depth 탐색 깊이
/// @return 집합의 블록 수
int dfs(int row, int col, int currId, char beforeColor, int depth)
{
    depth += 1;
    nodeNum[row][col] = currId;
    for (int i = 0; i < 4; ++i)
    {
        const int newRow = row + dx[i];
        const int newCol = col + dy[i];
        if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < M)
        {
            if (nodeNum[newRow][newCol] == 0 &&
                arr[newRow][newCol] == beforeColor)
                depth += dfs(newRow, newCol, currId, beforeColor, depth + 1);
        }
    }
    return depth;
}

/// @brief 색깔에 맞는 클러스터의 개수를 계산
/// @details 탐색할 범위가 10x10으로 크지 않기에 bfs를 이용해 탐색하기로 결정
/// @param ClusterNum 기준 집합 번호
/// @param color 탐색할 색깔
/// @return 인접한 집합 번호 배열 반환
vector<int> ConnectClusterCnt(int ClusterNum, char color)
{
    queue<pair<int, int>> q;
    set<int> s;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (sets[nodeNum[i][j]].first == ClusterNum) q.emplace(i, j);

    vector<int> result;

    while (!q.empty())
    {
        const int row = q.front().first;
        const int col = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            const int newRow = row + dx[i];
            const int newCol = col + dy[i];
            if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < M &&
                sets[nodeNum[newRow][newCol]].first != ClusterNum &&
                sets[nodeNum[newRow][newCol]].second == color &&
                s.find(sets[nodeNum[newRow][newCol]].first) == s.end())
            {
                s.insert(sets[nodeNum[newRow][newCol]].first);
                result.push_back(nodeNum[newRow][newCol]);
            }
        }
    }

    return result;
}

/// @brief 색깔에 맞는 클러스터의 블럭 개수를 계산
/// @details 탐색할 범위가 10x10으로 크지 않기에 bfs를 이용해 탐색하기로 결정
/// @param ClusterNum 기준 집합 번호
/// @param color 탐색할 색깔
/// @return 인접한 블럭 개수 반환
int ConnectBlockCnt(int ClusterNum, char color)
{
    queue<pair<int, int>> q;
    set<int> s;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (sets[nodeNum[i][j]].first == ClusterNum) q.emplace(i, j);

    int result = 0;

    while (!q.empty())
    {
        const int row = q.front().first;
        const int col = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            const int newRow = row + dx[i];
            const int newCol = col + dy[i];
            if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < M &&
                sets[nodeNum[newRow][newCol]].first != ClusterNum &&
                sets[nodeNum[newRow][newCol]].second == color &&
                s.find(sets[nodeNum[newRow][newCol]].first) == s.end())
            {
                s.insert(sets[nodeNum[newRow][newCol]].first);
                result += blockCnt[nodeNum[newRow][newCol]];
            }
        }
    }

    return result;
}

/// @brief 클러스터의 가장 왼쪽위 (위쪽이 더 우선순위 높음) 요소를 반환합니다.
/// @param cluster 집합 번호
/// @return 좌표
pair<int, int> FindTopLeftNode(int cluster)
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (sets[nodeNum[i][j]].first == cluster) return {i, j};
    return {-1, -1};
}

int main()
{
    cin >> N >> M >> T >> target;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) cin >> arr[i][j];

    int currentId = 1;

    /* 입력 */
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (nodeNum[i][j] == 0)
            {
                blockCnt.push_back(dfs(i, j, currentId, arr[i][j], 0));
                sets.emplace_back(currentId, arr[i][j]);

                currentId++;
            }

    while (T--)
    {
        int cluster;
        char color;
        vector<int> connectClusters;

        /* 타 색상과 가장 많이 연결되는 클러스터 찾기 */
        for (int i = 1; i <= currentId; ++i)
        {
            char colorArr[4] = {'R', 'G', 'B', 'Y'};
            for (auto& c : colorArr)
            {
                auto tmp = ConnectClusterCnt(i, c);
                if (tmp.size() > connectClusters.size())
                {
                    connectClusters = tmp;
                    cluster = i;
                    color = c;
                }
            }
        }
        int root;

        /* 칸 병합 */
        for (const auto& x : connectClusters)
        {
            sets[x].first = cluster;
            sets[x].second = color;
        }

        pair<int, int> coor = FindTopLeftNode(cluster);

        cout << coor.first << " " << coor.second << " " << color << "\n";
    }
}