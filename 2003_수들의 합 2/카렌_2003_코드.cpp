#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// �Է¿� �ʿ��� ���� ����� �ֱ�
	int N,M; 
	
	cin >> N >> M;
	
	// ���� ����� �ֱ� 
	vector<int> arr(N);
	for(int i = 0; i < N; i++) cin >> arr[i];
	
	// ���� �����ϴµ� �ʿ��� ���� ����� �ֱ�
	int left = 0, right = 0;
	int sum = 0;
	int count = 0;
	
	while(true)
	{
		if (sum >= M)
		{
			sum -= arr[left];
			left++;
		}
		else if (right == N) break;
		else
		{
			sum += arr[right];
			right++;
		}
		
		if(sum == M) count ++;
	}
	
	cout << count << "\n";
	return 0;
}
