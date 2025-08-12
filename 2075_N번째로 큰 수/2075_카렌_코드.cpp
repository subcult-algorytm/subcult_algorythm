#include <iostream>
#include <queue>

using namespace std;

int main()
{
	std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
	int N;
	cin >> N;
	
	//최소힙 구현이므로 greater<int>를 사용해준다.
	 
	priority_queue<int,vector<int>,greater<int>> minHeap;
	
	// 이중 반복문을 사용하여 N * N 만큼 값을 받는다. 
	 
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			int num;
			cin >> num;
			
			/*
			
			case 1.
			만약에  최소 힙이 N보다 작으면 그냥 받아 준다.
			
			case 2.
		 	최소 힙의 size가 N이라면? 현재 최소힙의 top()과 비교 후, 클  경우 교체해준다.
			  
			*/
			
			if(minHeap.size() < N) // 만약에 N보다 작다면? 
			{
				minHeap.push(num); // 그냥 넣어주는 부분 
			}else if(num > minHeap.top())  // 만약 최소 힙 크기가  N이고, num이 top보다 클 경우.   
			{
				minHeap.pop();
				minHeap.push(num);
			}
		}
	}
	
	cout << minHeap.top() << "\n";
	
	return 0; 
}
