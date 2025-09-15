#include <iostream>
#include <vector>

using namespace std;

int N, M, truth;

int parent[51];
vector<int> arr[51];

int find_(int x)
{
    if (x != parent[x])
        return parent[x] = find_(parent[x]);
    else
        return parent[x];
}

void merge(int a, int b)
{
    int left = find_(parent[a]);
    int right = find_(parent[b]);

    // 부모가 더 작은 숫자가 되도록 설정
    // 진실을 아는 그룹의 부모가 0이기에 작은 쪽을 따라가도록 설정
    if (left < right)
        parent[right] = left;
    else
        parent[left] = right;
}

int main()
{
    cin >> N >> M >> truth;

    for (int i = 1; i <= N; ++i) parent[i] = i;

    for (int i = 0; i < truth; ++i)
    {
        int tmp;
        cin >> tmp;
        parent[tmp] = 0;
    }

    for (int i = 0; i < M; ++i)
    {
        int people_cnt;
        int first_person;
        cin >> people_cnt;
        cin >> first_person;

        arr[i].push_back(first_person);
        for (int j = 1; j < people_cnt; ++j)
        {
            int tmp;
            cin >> tmp;
            arr[i].push_back(tmp);
            merge(first_person, tmp);
        }
    }

    int answer = M;  // 전부 거짓말부터 시작

    for (int i = 0; i < M; ++i)
        for (int j = 0; j < arr[i].size(); ++j)
        {
            if (find_(parent[arr[i][j]]) == 0)
            {
                answer--;
                break;
                // 한명이라도 진실을 알면 그 파티는 거짓말을 못함
            }
        }
    cout << answer;
}