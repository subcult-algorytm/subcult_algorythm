#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <utility> // pair 사용

using namespace std;

const int MAX_NODES = 10 * 10; // 최대 노드 수 임의 지정

int N, M;
int total_nodes; // 실제 노드 수 (N * M)
char target_color;
vector<char> my_colors = { 'r', 'g', 'b', 'y' };

int dy[4] = { 1, 0, -1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 세로 가로  목표 색상
    cin >> N >> M >> target_color;

    total_nodes = N * M;


    // 계산을 편하게 하기 위해 1차원 벡터로 색상 패턴을 저장
    // 중복 검사를 set.find 로 처리 예정
    vector<char> starting_map_colors(MAX_NODES, ' ');
    string input_str;
    for (int y = 0; y < N; y++)
    {
        cin >> input_str;
        for (int x = 0; x < M; x++)
            starting_map_colors[y * M + x] = input_str[x];
    }
    
    // 1번 BFS
    queue<pair<vector<char>, int>> q; // <맵 색상 패턴, 이동 횟수>
    set<vector<char>> visited; // 방문한 맵 색상 패턴들 저장용 set
    q.push({ starting_map_colors, 0 }); // 초기 색상 패턴, 이동횟수0
    visited.insert(starting_map_colors); // 초기 색상 패턴 (방문 경로)
    while (!q.empty())
    {
        vector<char> now_colors = q.front().first;
        int dist = q.front().second;
        q.pop();

        // 모두 원하는 색상으로 바뀌었다면 코드 중단 (문제 끗)
        bool isFlag = true;
        for (int i = 0; i < total_nodes; i++)
        {
            if (now_colors[i] != target_color)
            {
                isFlag = false;
                break;
            }
        }
        if (isFlag)
        {
            cout << dist;
            return 0;
        }


        // 해당 노드가 속한 그룹이 처리되었는지 확인하는용의 방문 배열
        vector<bool> visited_nodes(MAX_NODES, false);

        // 모든 노드 순회
        for (int node_index = 0; node_index < total_nodes; node_index++)
        {
            // 해당 노드가 속한 그룹이 미방문일때만 진행
            if (!visited_nodes[node_index])
            {
                char original_color = now_colors[node_index];

                // 2번 BFS (실제 노드 그룹 탐색)
                vector<int> color_group_nodes;
                queue<int> q_group;
                vector<bool> node_group_visited(MAX_NODES, false);
                q_group.push(node_index);
                node_group_visited[node_index] = true;
                while (!q_group.empty())
                {
                    int now_color_group_nodes = q_group.front();
                    q_group.pop();
                    color_group_nodes.push_back(now_color_group_nodes);

                    // 1차원에 저장한 색상패턴을 다시 좌표로 보정
                    int current_y = now_color_group_nodes / M;
                    int current_x = now_color_group_nodes % M;
                    for (int i = 0; i < 4; i++)
                    {
                        int next_y = current_y + dy[i];
                        int next_x = current_x + dx[i];

                        // 맵 범위 (0-index 헷갈리지 않기)
                        if (next_y >= 0 && next_y < N && next_x >= 0 && next_x < M)
                        {
                            int next_node_index = next_y * M + next_x;
                            // 아직 방문 안 했고, 오리지널과 새로 방문한 색상이 같다면 다음 BFS 추가
                            if (!node_group_visited[next_node_index]
                                && now_colors[next_node_index] == original_color)
                            {
                                node_group_visited[next_node_index] = true;
                                q_group.push(next_node_index);
                            }
                        }
                    }
                }

                // 방문 기록 (visit)
                for (int group_node_index : color_group_nodes)
                    visited_nodes[group_node_index] = true;

                // 본인을 제외한 다른 색(3색)으로 모두 검사 (이걸 c로 잡을때 O(c^nm)
                for (char next_color : my_colors)
                {
                    if (next_color == original_color) continue; // 동일 색상 skip

                    // 다음 색상 상태 벡터 생성 및 색상 변경
                    vector<char> next_colors = now_colors; // 현재 상태 복사
                    for (int group_node_index : color_group_nodes) // 노드 그룹 내 모든 노드에 대해
                        next_colors[group_node_index] = next_color; // 색상 변경 적용

					// set.find로 중복 검사, 이미 기록된 패턴이라면 dist가 더 크므로 skip - 1번 bfs의 최단 탐색을 지켜야 함
                    if (visited.find(next_colors) == visited.end())
                    {
                        visited.insert(next_colors); // 방문 셋에 추가
                        q.push({ next_colors, dist + 1 }); // 1번 bfs에 다음 색상과 거리 추가
                    }
                }
            }
        }
    }

    return 0;
}
