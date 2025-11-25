#include <iostream>
#include <algorithm>

using namespace std;

int heap[100001];
int sz = 0; // 현재 힙 개수  

void push(int x)
{
	heap[++sz] = x; // 맨 끝에 넣는다 
	
	int index = sz; 
	
	/*
	부모보다 자식이 더 크다면 계속 올린다. 
	*/
	while(index > 1)
	{
		int parent = index / 2;
		
		if(heap[index]>heap[parent])
		{
			swap(heap[index],heap[parent]);
			index = parent;
		}else{
			break; // 부모보다 작거나 같으면 멈춘다. 
		}
	}
}

int pop()
{
	if (sz == 0) return 0;
	
	int result = heap[1];
	
	heap[1] = heap[sz];
	sz--;
	
	int index = 1;
	
	while(index * 2 <= sz)
	{
		int left = index * 2;
		int right = index * 2 + 1;
		int larger_child = left; // 일단 왼쪽이라고 둠
		
		// 오른쪽 자식이 있고, 오른쪽이 왼쪽보다 크다면 더 큰 쪽을 선택 
		
		if(right <= sz && heap[right] > heap[left])
		{
			larger_child = right; 	
		} 
		
		// 부모가 자식 보다 작다면 교체 
		if(heap[index] < heap[larger_child])
		{
			swap(heap[index],heap[larger_child]);
			index = larger_child;	
		} else
		{
			break;
		}
	}
	
	return result; 
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N; 
    
    cin >> N;
    
    while(N--)
    {
    	int x;
    	cin >> x; 
    	if(x == 0)
    	{
    		cout << pop() << "\n";
		}else{
			push(x);
		}
 
	}
	
	return 0;
}
