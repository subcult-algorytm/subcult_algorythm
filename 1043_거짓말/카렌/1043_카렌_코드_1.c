#include <stdio.h>
#include <stdbool.h>

int N, M; // N: 사람수 , M: 파티수
bool knows_truth[51]; // 진실을 알고 있느냐의 여부
int parties[50][51];     // parties[i][0] 은 해당 파티의 참여 인원
// parties[i][j] 은 i번째의 j번째 참여자의 아이디를 담는다.

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i <= N; i++) {
        knows_truth[i] = false;
    }

    // 초기 진실을 아는 사람 정보 입력 받기
    int initial_truth_knowers_count;
    scanf("%d", &initial_truth_knowers_count);
    for (int i = 0; i < initial_truth_knowers_count; i++) {
        int person_id;
        scanf("%d", &person_id);
        knows_truth[person_id] = true;
    }

    // 각 파티 정보 입력 받기
    for (int i = 0; i < M; i++) {
        scanf("%d", &parties[i][0]);
        for (int j = 1; j <= parties[i][0]; j++) {
            scanf("%d", &parties[i][j]);
        }
    }

    // 진실을 전파하는 로직
    bool changed_in_iteration;
    do {
        changed_in_iteration = false;
        for (int i = 0; i < M; i++) {
            bool party_has_truth_knower = false;
            // 현재 파티에 진실을 아는 사람이 있는지 확인
            for (int j = 1; j <= parties[i][0]; j++) {
                if (knows_truth[parties[i][j]]) {
                    party_has_truth_knower = true;
                    break;
                }
            }

            if (party_has_truth_knower) {
                // 파티에 진실을 하는 사람이 있다면, 파티의 모든 사람들에게 진실을 전파한다
                for (int j = 1; j <= parties[i][0]; j++) {
                    if (!knows_truth[parties[i][j]]) {
                        knows_truth[parties[i][j]] = true;
                        changed_in_iteration = true; // 상태변경
                    }
                }
            }
        }
    } while (changed_in_iteration);

    // 거짓말을 할 수 있는 파티 세기
    int lie_party_count = 0;
    for (int i = 0; i < M; i++) {
        bool can_lie_at_this_party = true;
        for (int j = 1; j <= parties[i][0]; j++) {
            {
                if (knows_truth[parties[i][j]]) {
                    can_lie_at_this_party = false;
                    break;
                }
            }
            if (can_lie_at_this_party) {
                lie_party_count++;
            }
        }

        printf("%d\n", lie_party_count);

        return 0;


    }