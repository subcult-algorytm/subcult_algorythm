#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

int N, M, T;
char target;

int arr[10][10];
int nodeNum[10][10];
vector<pair<int, char>> sets(1);  // 각 집합의 <부모, 색깔> 집합
vector<int> blockCnt(1);          // 각 집합의 블록 수
map<char, set<int>> colors;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void dfs(int row, int col, int currId, char beforeColor, unique_ptr<int>& depth)
{
    *depth += 1;
    nodeNum[row][col] = currId;
    for (int i = 0; i < 4; ++i)
    {
        const int newRow = row + dx[i];
        const int newCol = col + dy[i];
        if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < M)
        {
            if (nodeNum[newRow][newCol] == 0 && arr[newRow][newCol] == beforeColor)
                dfs(newRow, newCol, currId, beforeColor, depth);
        }
    }
}

vector<pair<pair<int, int>, char>> CrossOver(vector<pair<pair<int, int>, char>>& gene1,
                                             vector<pair<pair<int, int>, char>>& gene2)
{
    int cross_over_point = rand() % T;

    vector<pair<pair<int, int>, char>> child;
    child.resize(cross_over_point);

    copy_n(gene1.begin(), cross_over_point, child.begin());
    child.resize(T);
    copy_n(gene2.begin(), T - cross_over_point, child.begin() + cross_over_point);

    return child;
}

int Fitness(vector<pair<pair<int, int>, char>> gene)
{
    int result = 0;
    for (auto& i : gene)
    {
        auto idx = nodeNum[i.first.first][i.first.second];
        if (sets[idx].second == target) result += blockCnt[idx];
    }

    return result;
}

void Mutate(vector<pair<pair<int, int>, char>>& gene, int percent)
{
    for (auto& j : gene)
    {
        if (rand() % 100 < percent)
        {
            int choice = rand() % 4;
            if (choice == 0)
                j.second = 'R';
            else if (choice == 1)
                j.second = 'B';
            else if (choice == 2)
                j.second = 'G';
            else if (choice == 3)
                j.second = 'Y';
        }
    }
}

int main()
{
    cin >> N >> M >> T >> target;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) cin >> arr[i][j];

    int currentId = 1;
    int gene_cnt = 500;

    /* 입력 */
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (nodeNum[i][j] == 0)
            {
                unique_ptr<int> ptr = make_unique<int>(0);

                dfs(i, j, currentId, arr[i][j], ptr);
                blockCnt.push_back(*ptr);
                sets.emplace_back(currentId, arr[i][j]);

                colors[arr[i][j]].insert(currentId);

                currentId++;
            }

    vector<vector<pair<pair<int, int>, char>>> genes;

    for (int i = 0; i < gene_cnt; ++i)
    {
        vector<pair<pair<int, int>, char>> tmp;
        for (int j = 0; j < T; ++j)
        {
            int choice = rand() % 4;
            if (choice == 0)
                tmp.push_back({{rand() % N, rand() % M}, 'R'});
            else if (choice == 1)
                tmp.push_back({{rand() % N, rand() % M}, 'G'});
            else if (choice == 2)
                tmp.push_back({{rand() % N, rand() % M}, 'B'});
            else if (choice == 3)
                tmp.push_back({{rand() % N, rand() % M}, 'Y'});
        }
    }

    while (true)
    {
        int scores = 0;

        vector<pair<int, vector<pair<pair<int, int>, char>>>> select_genes;

        for (auto& gene : genes)
        {
            int score = Fitness(gene);
            if (score == N * M)
            {
                for (auto& i : gene)
                {
                    if (i.second == 0)
                        cout << i.first.first << " " << i.first.second << " R\n";
                    else if (i.second == 1)
                        cout << i.first.first << " " << i.first.second << " G\n";
                    else if (i.second == 2)
                        cout << i.first.first << " " << i.first.second << " B\n";
                    else if (i.second == 3)
                        cout << i.first.first << " " << i.first.second << " Y\n";
                }
                return 0;
            }
            select_genes.push_back({-score, gene});
        }

        sort(select_genes.begin(), select_genes.end());

        select_genes.erase(select_genes.begin() + select_genes.size() / 2, select_genes.end());

        vector<vector<pair<pair<int, int>, char>>> next_genes;

        for (int i = 0; i < genes.size(); ++i)
        {
            next_genes.push_back(CrossOver(select_genes[rand() % select_genes.size()].second,
                                           select_genes[rand() % select_genes.size()].second));
        }

        for (auto& next_gene : next_genes) Mutate(next_gene, 5);

        genes = next_genes;
    }
}