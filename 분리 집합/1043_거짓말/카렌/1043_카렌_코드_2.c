// 1. 헤더 파일 포함 및 전역 변수 선언

#include <stdio.h>
#include <stdbool.h>

int parent[51]; // 각 대표를 저장하는 배열

int N, M; // N: 사람 수, M: 파티 수
int parties_info[50][51];
//  parties_info[i][0]: i번째 파티의 참석자 수
//  parties_info[i][1]부터: i번째 파티 참석자 ID
int initial_truth_knowers[51];
bool set_knows_truth[51];

// 2. Union-Find 관련 함수 정의 

// Union-find 자료구조를 초기화 하는 함수이다. 

void init_union_find(int n)
{
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i; // 자기 자신을 대표로 설정
    }
}

// 특정 원소 v가 속한 집합의 대표를 찾아주는 함수이다. 
int find_set_representative(int v)
{
    if (v == parent[v]) // 자기 자신이 대표이면 자신을 반환한다.
        return v;
    //아니면 재귀 함수를 사용해서 대표를 가리키도록 한다.
    return parent[v] = find_set_representative(parent[v]);
}

void unite_sets(int a, int b)
{
    a = find_set_representative(a);
    b = find_set_representative(b);
    if (a != b) // 서로의 대표가 다를 경우
    {
        parent[b] = a;
    }
}

// 3. 입력 및 Union-Find 초기화 

int main() {

    scanf("%d %d", &N, &M);

    init_union_find(N);

    // 처음에 진실을 아는 사람의 수와 ID를 입력해준다.
    int num_initial_knowers;
    scanf("%d", &num_initial_knowers);
    for (int i = 0; i < num_initial_knowers; i++)
    {
        scanf("%d", &initial_truth_knowers[i]);
    }

    // 전에 입력받은 M 만큼 파티의 정보들을 입력 받는다.

    // 4. 파티 정보 처리 및 집합 형성

    for (int i = 0; i < M; i++)
    {
        scanf("%d", &parties_info[i][0]); // i번째 파티의 참석자 수 

        if (parties_info[i][0] > 0) // 파티에 참석자가 1명 이상일 경우
        {
            //우선 첫번째 참석자의 ID를 읽어준다. 
            scanf("%d", &parties_info[i][1]);
            //두 번째 참석자부터는 첫 번째 참석자와 같은 집합으로 합쳐준다.
            for (int j = 2; j <= parties_info[i][0]; j++) {
                scanf("%d", &parties_info[i][j]);
                unite_sets(parties_info[i][1], parties_info[i][j]);
            }
        }
    }

    //5. 진실을 아는 집합 표시

    // 처음엔 모두 진실을 모른다고 가정하고 false로 초기화 해준다.
    for (int i = 1; i <= N; i++)
    {
        set_knows_truth[i] = false;
    }

    // 처음에 진실을 알던 사람들을 이용해 set_knows_truth 배열의 값을 바꿔준다.
    for (int i = 0; i < num_initial_knowers; i++)
    {
        int person_id = initial_truth_knowers[i];
        int root_of_person = find_set_representative(person_id);
        set_knows_truth[root_of_person] = true;
    }

    // 6. 거짓말을 할 수 있는 파티 계산

    //처음에 거짓말을 할 수 있는 파티의 수를 0으로 설정한다.
    int lie_party_count = 0;
    for (int i = 0; i < M; i++)
    {
        //일단 처음엔 현재 파티에서 거짓말이 가능하다고 가정한다.
        bool can_lie_at_this_party = true;
        for (int j = 1; j <= parties_info[i][0]; j++)
        {
            int attendee_id = parties_info[i][j];
            int root_of_attendee = find_set_representative(attendee_id);
            if (set_knows_truth[root_of_attendee])
            {
                can_lie_at_this_party = false;
                break;
            }
        }
        // 만약 무사히 넘어갔다면 
        if (can_lie_at_this_party) {
            lie_party_count++;
        }
    }

    //7. 결과 출력
    printf("%d\n", lie_party_count);

    return 0;
}