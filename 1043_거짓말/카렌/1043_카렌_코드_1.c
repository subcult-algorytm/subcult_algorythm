#include <stdio.h>
#include <stdbool.h>

int N, M; // N: ����� , M: ��Ƽ��
bool knows_truth[51]; // ������ �˰� �ִ����� ����
int parties[50][51];     // parties[i][0] �� �ش� ��Ƽ�� ���� �ο�
// parties[i][j] �� i��°�� j��° �������� ���̵� ��´�.

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i <= N; i++) {
        knows_truth[i] = false;
    }

    // �ʱ� ������ �ƴ� ��� ���� �Է� �ޱ�
    int initial_truth_knowers_count;
    scanf("%d", &initial_truth_knowers_count);
    for (int i = 0; i < initial_truth_knowers_count; i++) {
        int person_id;
        scanf("%d", &person_id);
        knows_truth[person_id] = true;
    }

    // �� ��Ƽ ���� �Է� �ޱ�
    for (int i = 0; i < M; i++) {
        scanf("%d", &parties[i][0]);
        for (int j = 1; j <= parties[i][0]; j++) {
            scanf("%d", &parties[i][j]);
        }
    }

    // ������ �����ϴ� ����
    bool changed_in_iteration;
    do {
        changed_in_iteration = false;
        for (int i = 0; i < M; i++) {
            bool party_has_truth_knower = false;
            // ���� ��Ƽ�� ������ �ƴ� ����� �ִ��� Ȯ��
            for (int j = 1; j <= parties[i][0]; j++) {
                if (knows_truth[parties[i][j]]) {
                    party_has_truth_knower = true;
                    break;
                }
            }

            if (party_has_truth_knower) {
                // ��Ƽ�� ������ �ϴ� ����� �ִٸ�, ��Ƽ�� ��� ����鿡�� ������ �����Ѵ�
                for (int j = 1; j <= parties[i][0]; j++) {
                    if (!knows_truth[parties[i][j]]) {
                        knows_truth[parties[i][j]] = true;
                        changed_in_iteration = true; // ���º���
                    }
                }
            }
        }
    } while (changed_in_iteration);

    // �������� �� �� �ִ� ��Ƽ ����
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