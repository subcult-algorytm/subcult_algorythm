#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

//priority_queue�� ���� cmp ���� 
 
struct cmp
{
	bool operator()(int a,int b) // ������ ���۷�����
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
		
		if(x == 0) // x�� 0�� ������ ��� 
		{
			if(pq.empty()) // pq�� ����� ��� 
			{
				cout << 0 << endl;	
			}
			else // pq�� ������� ���� ��� 
			{
				cout << pq.top() << endl;
				pq.pop();
			}
		}
		else // x�� 0�� ������ �ʾ��� ���  
		{
			pq.push(x);
		}	
	}
	
	return 0;
}
