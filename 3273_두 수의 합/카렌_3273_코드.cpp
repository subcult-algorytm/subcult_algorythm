#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	// 배열의 크기 입력 받기
	int N;
	cin >> N;
	
	//배열 만들기 
	vector<int> arr(N);
	for(int i =0; i<N; i++)cin >> arr[i];
	
	int x;
	cin >> x;
	
	//투포인터를 위한 배열 정렬
	sort(arr.begin(),arr.end());
	
	//투포인터 구현을 위한 변수 선언
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
