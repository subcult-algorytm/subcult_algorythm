// 기존의 연산을 재사용
// 배열: array[값] = 1로 만드는데 필요한 연산수 

#include <stdio.h>
#define MAX_SIZE 1000001

int main()
{

	int input = 0;

	scanf("%d", &input);

	int array[MAX_SIZE];

	array[1] = 0; // 1은 별도의 연산이 필요 없으므로 

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

	// -1 은 모든 수가 가능하니까 기본 연산으로 두고 혹시 더 나은 선택지가 있으면 배열의 값을 교체. 

	printf("%d\n", array[input]);
	return 0;
}