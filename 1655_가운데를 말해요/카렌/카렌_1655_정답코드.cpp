#include <iostream>
#include <vector>
#include <queue>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	
	int N;
	std::cin >> N;
	
	/*
	CPP�� �⺻������
	
	�ִ���,������������ �켱����ť�� ������ �ȴ�.
	
	����, �ּ����� ���� �ϰ� �������� ��������� ������ ��Ÿ������Ѵ�.
	 
	*/
	
	// �ִ��� 
	std::priority_queue<int> max_heap;
	
	//std::priority_queue<int,std::vector<int>,std::less<int>> max heap;
	
	std::priority_queue<int,std::vector<int>,std::greater<int>> min_heap;
	
	for(int i = 0; i <N; ++i)
	{
		int num;
		std::cin >> num;
		
		/*
		1. �� ���� size�� ��������Ѵ�.
		
		�ִ� ���� size�� �ּ� ���� size���� ���ų� 1 Ŀ���Ѵ�.
		 
		*/
		
		if(max_heap.size()==min_heap.size())
		{
			max_heap.push(num);
		}
		else
		{
			min_heap.push(num);
		}
		
		/*
		
		2. 
		 
		�ּ� ���� ��� ���� �ִ� ���� ��� �� �̻��̿��� �Ѵ�.
		
		���� �� ��Ģ�� ��Ű�� �� �� ��� �� top�� ���� swap �������μ�
		
		�� ��Ģ�� �ڿ� ������ ���� ��Ų��.  
		*/ 
		
		if(!min_heap.empty() && (max_heap.top() > min_heap.top()))
		{
			int max_val = max_heap.top();
			int min_val = min_heap.top();
			
			max_heap.pop();
			min_heap.pop();
			
			max_heap.push(min_val);
			min_heap.push(max_val);
			
			// �߰� ���� �ִ� ���� top �̴�.
			
			
		} 
		
		std::cout << max_heap.top() << '\n';
		
	}
	
	return 0;  

}
