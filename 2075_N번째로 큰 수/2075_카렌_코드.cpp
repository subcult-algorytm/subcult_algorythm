#include <iostream>
#include <queue>

using namespace std;

int main()
{
	std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
	int N;
	cin >> N;
	
	//�ּ��� �����̹Ƿ� greater<int>�� ������ش�.
	 
	priority_queue<int,vector<int>,greater<int>> minHeap;
	
	// ���� �ݺ����� ����Ͽ� N * N ��ŭ ���� �޴´�. 
	 
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			int num;
			cin >> num;
			
			/*
			
			case 1.
			���࿡  �ּ� ���� N���� ������ �׳� �޾� �ش�.
			
			case 2.
		 	�ּ� ���� size�� N�̶��? ���� �ּ����� top()�� �� ��, Ŭ  ��� ��ü���ش�.
			  
			*/
			
			if(minHeap.size() < N) // ���࿡ N���� �۴ٸ�? 
			{
				minHeap.push(num); // �׳� �־��ִ� �κ� 
			}else if(num > minHeap.top())  // ���� �ּ� �� ũ�Ⱑ  N�̰�, num�� top���� Ŭ ���.   
			{
				minHeap.pop();
				minHeap.push(num);
			}
		}
	}
	
	cout << minHeap.top() << "\n";
	
	return 0; 
}
