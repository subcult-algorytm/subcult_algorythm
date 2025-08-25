#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// 입력에 필요한 변수 만들어 주기
	int N,M; 
	
	cin >> N >> M;
	
	// 벡터 만들어 주기 
	vector<int> arr(N);
	for(int i = 0; i < N; i++) cin >> arr[i];
	
	// 범위 설정하는데 필요한 변수 만들어 주기
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
