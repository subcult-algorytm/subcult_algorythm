// 1. ��� ���� ���� �� ���� ���� ����

#include <stdio.h>
#include <stdbool.h>

int parent[51]; // �� ��ǥ�� �����ϴ� �迭

int N, M; // N: ��� ��, M: ��Ƽ ��
int parties_info[50][51];
//  parties_info[i][0]: i��° ��Ƽ�� ������ ��
//  parties_info[i][1]����: i��° ��Ƽ ������ ID
int initial_truth_knowers[51];
bool set_knows_truth[51];

// 2. Union-Find ���� �Լ� ���� 

// Union-find �ڷᱸ���� �ʱ�ȭ �ϴ� �Լ��̴�. 

void init_union_find(int n)
{
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i; // �ڱ� �ڽ��� ��ǥ�� ����
    }
}

// Ư�� ���� v�� ���� ������ ��ǥ�� ã���ִ� �Լ��̴�. 
int find_set_representative(int v)
{
    if (v == parent[v]) // �ڱ� �ڽ��� ��ǥ�̸� �ڽ��� ��ȯ�Ѵ�.
        return v;
    //�ƴϸ� ��� �Լ��� ����ؼ� ��ǥ�� ����Ű���� �Ѵ�.
    return parent[v] = find_set_representative(parent[v]);
}

void unite_sets(int a, int b)
{
    a = find_set_representative(a);
    b = find_set_representative(b);
    if (a != b) // ������ ��ǥ�� �ٸ� ���
    {
        parent[b] = a;
    }
}

// 3. �Է� �� Union-Find �ʱ�ȭ 

int main() {

    scanf("%d %d", &N, &M);

    init_union_find(N);

    // ó���� ������ �ƴ� ����� ���� ID�� �Է����ش�.
    int num_initial_knowers;
    scanf("%d", &num_initial_knowers);
    for (int i = 0; i < num_initial_knowers; i++)
    {
        scanf("%d", &initial_truth_knowers[i]);
    }

    // ���� �Է¹��� M ��ŭ ��Ƽ�� �������� �Է� �޴´�.

    // 4. ��Ƽ ���� ó�� �� ���� ����

    for (int i = 0; i < M; i++)
    {
        scanf("%d", &parties_info[i][0]); // i��° ��Ƽ�� ������ �� 

        if (parties_info[i][0] > 0) // ��Ƽ�� �����ڰ� 1�� �̻��� ���
        {
            //�켱 ù��° �������� ID�� �о��ش�. 
            scanf("%d", &parties_info[i][1]);
            //�� ��° �����ں��ʹ� ù ��° �����ڿ� ���� �������� �����ش�.
            for (int j = 2; j <= parties_info[i][0]; j++) {
                scanf("%d", &parties_info[i][j]);
                unite_sets(parties_info[i][1], parties_info[i][j]);
            }
        }
    }

    //5. ������ �ƴ� ���� ǥ��

    // ó���� ��� ������ �𸥴ٰ� �����ϰ� false�� �ʱ�ȭ ���ش�.
    for (int i = 1; i <= N; i++)
    {
        set_knows_truth[i] = false;
    }

    // ó���� ������ �˴� ������� �̿��� set_knows_truth �迭�� ���� �ٲ��ش�.
    for (int i = 0; i < num_initial_knowers; i++)
    {
        int person_id = initial_truth_knowers[i];
        int root_of_person = find_set_representative(person_id);
        set_knows_truth[root_of_person] = true;
    }

    // 6. �������� �� �� �ִ� ��Ƽ ���

    //ó���� �������� �� �� �ִ� ��Ƽ�� ���� 0���� �����Ѵ�.
    int lie_party_count = 0;
    for (int i = 0; i < M; i++)
    {
        //�ϴ� ó���� ���� ��Ƽ���� �������� �����ϴٰ� �����Ѵ�.
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
        // ���� ������ �Ѿ�ٸ� 
        if (can_lie_at_this_party) {
            lie_party_count++;
        }
    }

    //7. ��� ���
    printf("%d\n", lie_party_count);

    return 0;
}