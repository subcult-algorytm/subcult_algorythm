#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	
	priority_queue<int,vector<int>,greater<int>> pq;
	
	// 1. 최소힙 만들기
	
	for(int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		pq.push(x);	
	} 
	
	int total_cost = 0;
	
	// 2. 묶음이 하나가 될 때 까지 반복 해 준다.
	
	while(pq.size() > 1)
	{
		// 가장 작은 두 묶음 꺼낸다.
		int a = pq.top(); pq.pop();
		int b = pq.top(); pq.pop();
		
		// 비용 발생 및 누적
		int sum = a+b;
		total_cost += sum;	
		
		// 합친 묶음을 다시 힙에 넣어서 다음 비교에 포함 시켜야 한다. 
		
		pq.push(sum);	
	}
	
	cout << total_cost << "\n";

	return 0; 
}
