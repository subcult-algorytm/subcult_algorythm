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
	CPP는 기본적으로
	
	최대힙,내립차순으로 우선순위큐가 구현이 된다.
	
	만약, 최소힙을 구현 하고 싶을때는 명시적으로 형식을 나타내줘야한다.
	 
	*/
	
	// 최대힙 
	std::priority_queue<int> max_heap;
	
	//std::priority_queue<int,std::vector<int>,std::less<int>> max heap;
	
	std::priority_queue<int,std::vector<int>,std::greater<int>> min_heap;
	
	for(int i = 0; i <N; ++i)
	{
		int num;
		std::cin >> num;
		
		/*
		1. 두 힙의 size를 맞춰줘야한다.
		
		최대 힙의 size는 최소 힙의 size보다 같거나 1 커야한다.
		 
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
		 
		최소 힙의 모든 값은 최대 힙의 모든 값 이상이여야 한다.
		
		만약 이 규칙을 지키지 못 할 경우 두 top의 값을 swap 해줌으로서
		
		이 규칙을 자연 스럽게 충족 시킨다.  
		*/ 
		
		if(!min_heap.empty() && (max_heap.top() > min_heap.top()))
		{
			int max_val = max_heap.top();
			int min_val = min_heap.top();
			
			max_heap.pop();
			min_heap.pop();
			
			max_heap.push(min_val);
			min_heap.push(max_val);
			
			// 중간 값은 최대 힙의 top 이다.
			
			
		} 
		
		std::cout << max_heap.top() << '\n';
		
	}
	
	return 0;  

}
