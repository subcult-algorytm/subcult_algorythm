#include <stdio.h>
#include <limits.h> // INT_MAX �� ����ϱ� ���� ����


#define MAX_N 100001

int min(int a, int b) {
    return a < b ? a : b;
}

int main()
{
    int N;
    long long Sum;
    int array[MAX_N];

    if (scanf("%d %lld", &N, &Sum) != 2) {
        fprintf(stderr, "N�� Sum �Է� ����!\n");
        return 1;
    }

    if (N <= 0 || N >= MAX_N) {
        fprintf(stderr, "N ���� ��ȿ ������ ������ϴ� (1 ~ %d).\n", MAX_N - 1);
        return 1;
    }


    for (int i = 0; i < N; i++) {
        if (scanf("%d", &array[i]) != 1) {
            fprintf(stderr, "�迭 ���� �Է� ���� (�ε��� %d)!\n", i);
            return 1;
        }
    }

    int start = 0;
    int end = 0;
    long long current_sum = 0;
    int min_length = INT_MAX;

    while (end < N) {

        current_sum += array[end];

        while (current_sum >= Sum && start <= end) {
            min_length = min(min_length, end - start + 1);

            current_sum -= array[start];
            start++;
        }

        end++;
    }

    if (min_length == INT_MAX) {
        printf("0\n");
    }
    else {
        printf("%d\n", min_length);
    }
    return 0;
}