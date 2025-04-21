#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Colors
{
    set<int> R;
    set<int> G;
    set<int> B;
    set<int> Y;
};

int N, M, T;

char arr[10][10];         // 각 칸의 색깔
int nodeNum[10][10];      // 각 노드의 집합 번호
vector<int> sets(1);      // 각 집합의 부모 집합 (Union-Find 사용 예정)
vector<int> blockCnt(1);  // 각 집합의 블록 수
Colors colors;            // 나중에 같은 색깔에 있는지 확인할 트리

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

/// @brief 주어진 블럭이 주어진 색깔로 바뀌었을때 연결되는 같은 색깔 주변 블록
/// 개수 연산
/// @param changeColor 바꿀 색깔
/// @param row 바꿀 블록 행
/// @param col 바꿀 블록 열
/// @return 연결되는 블록 수
int connectedSets(char changeColor, int row, int col)
{
    char originalColor = arr[row][col];
    arr[row][col] = changeColor;
    int result = 0;

    for (int i = 0; i < 4; ++i)
    {
        const int newRow = row + dx[i];
        const int newCol = col + dy[i];
        if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < M)
        {
            int root = sets[nodeNum[newRow][newCol]];

            if (changeColor == 'R' && colors.R.end() != colors.R.find(root))
                result += blockCnt[root];
            else if (changeColor == 'G' &&
                     colors.G.end() != colors.G.find(root))
                result += blockCnt[root];
            else if (changeColor == 'B' &&
                     colors.B.find(root) != colors.B.end())
                result += blockCnt[root];
            else if (changeColor == 'Y' &&
                     colors.Y.find(root) != colors.Y.end())
                result += blockCnt[root];
        }
    }

    return result;
}

/// @brief 주어진 집합의 부모를 루트 노드로 바꿉니다
/// @param fromNode 바뀔 집합 번호
/// @param rootNum 루트 집합 번호
/// @param c 바뀐 색깔
void nodeColorChange(int fromNode, int rootNum, char c)
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
        {
            if (nodeNum[i][j] == fromNode)
            {
                arr[i][j] = c;
                nodeNum[i][j] = rootNum;
            }
        }
}

int main()
{
    cin >> N >> M >> T;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) cin >> arr[i][j];

    int currentId = 1;

    /* 입력 */
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (nodeNum[i][j] == 0)
            {
                blockCnt.push_back(dfs(i, j, currentId, arr[i][j], 0));
                sets.push_back(currentId);
                if (arr[i][j] == 'R')
                    colors.R.insert(currentId);
                else if (arr[i][j] == 'G')
                    colors.G.insert(currentId);
                else if (arr[i][j] == 'B')
                    colors.B.insert(currentId);
                else if (arr[i][j] == 'Y')
                    colors.Y.insert(currentId);

                currentId++;
            }

    while (T--)
    {
        int row, col;
        char color;
        int connectBlocksCntResult = 0;

        /* 병합할 시 가장 많이 연결되는 칸 찾기 */
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
            {
                char tmp[4]{'R', 'G', 'B', 'Y'};
                for (int k = 0; k < 4; ++k)
                {
                    if (tmp[k] == arr[i][j]) continue;
                    int connectBlocks = connectedSets(tmp[k], i, j);
                    if (connectBlocks > connectBlocksCntResult)
                    {
                        connectBlocksCntResult = connectBlocks;
                        row = i;
                        col = j;
                        color = tmp[k];
                    }
                }
            }

        int root;

        /* 근처 칸 집합에 바꿀 색깔의 루트 집합 찾기 */
        for (int i = 0; i < 4; ++i)
        {
            const int newRow = row + dx[i];
            const int newCol = col + dy[i];
            if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < M)
            {
                if (color == arr[newRow][newCol])
                    root = sets[nodeNum[newRow][newCol]];
            }
        }

        /* 칸 병합 */
        for (int i = 0; i < 4; ++i)
        {
            const int newRow = row + dx[i];
            const int newCol = col + dy[i];
            if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < M)
            {
                if (color != arr[newRow][newCol])
                {
                    sets[nodeNum[newRow][newCol]] = root;
                    nodeColorChange(sets[nodeNum[newRow][newCol]], root, color);
                }
            }
        }
        cout << row << " " << col << " " << color << "\n";
    }
}