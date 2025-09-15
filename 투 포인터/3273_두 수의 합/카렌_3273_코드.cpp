#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	// �迭�� ũ�� �Է� �ޱ�
	int N;
	cin >> N;
	
	//�迭 ����� 
	vector<int> arr(N);
	for(int i =0; i<N; i++)cin >> arr[i];
	
	int x;
	cin >> x;
	
	//�������͸� ���� �迭 ����
	sort(arr.begin(),arr.end());
	
	//�������� ������ ���� ���� ����
	int left = 0, right = N - 1;
	int count = 0;
	
	while(left < right)
	{
		int sum = arr[left] + arr[right];
		
		if(sum == x)
		{
			count++;
			left++;
			right--;
		}
		else if (sum < x)
		{
			left++;	
		}else
		{
			right--;
		}
	}
	
	cout << count << "\n";
}
