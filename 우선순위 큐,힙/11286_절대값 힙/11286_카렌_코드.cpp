#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

//priority_queue에 쓰일 cmp 구현 
 
struct cmp
{
	bool operator()(int a,int b) // 연산자 오퍼레이터
	{
		if(abs(a) == abs(b))
			return a > b;
		return abs(a) > abs(b);
	}	 
}; 

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	
	priority_queue<int,vector<int>,cmp> pq;
	
	for(int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		
		if(x == 0) // x에 0이 들어왔을 경우 
		{
			if(pq.empty()) // pq가 비었을 경우 
			{
				cout << 0 << endl;	
			}
			else // pq가 비어있지 않을 경우 
			{
				cout << pq.top() << endl;
				pq.pop();
			}
		}
		else // x에 0이 들어오지 않았을 경우  
		{
			pq.push(x);
		}	
	}
	
	return 0;
}
