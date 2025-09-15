// ������ ������ ����
// �迭: array[��] = 1�� ����µ� �ʿ��� ����� 

#include <stdio.h>
#define MAX_SIZE 1000001

int main()
{

	int input = 0;

	scanf("%d", &input);

	int array[MAX_SIZE];

	array[1] = 0; // 1�� ������ ������ �ʿ� �����Ƿ� 

	for (int i = 2; i <= input; i++)
	{
		array[i] = array[i - 1] + 1;

		if (i % 2 == 0)
		{
			if (array[i] > array[i / 2] + 1) {
				array[i] = array[i / 2] + 1;
			}
		}

		if (i % 3 == 0)
		{
			if (array[i] > array[i / 3] + 1) {
				array[i] = array[i / 3] + 1;
			}
		}
	}

	// -1 �� ��� ���� �����ϴϱ� �⺻ �������� �ΰ� Ȥ�� �� ���� �������� ������ �迭�� ���� ��ü. 

	printf("%d\n", array[input]);
	return 0;
}