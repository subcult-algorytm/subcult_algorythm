#include <iostream>
#include <queue>

using namespace std;

int main()
{
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	
	priority_queue<int> pq;
	
	for(int i =0 ; i < N; i++)
	{
		int num; 
		cin >> num;
		
		if(num == 0)
		{
			if(pq.empty())
			{
				cout << "-1" << "\n";
			}
			else
			{
				cout << pq.top() << "\n";
				pq.pop();
			}
		}
		else
		{
			for(int j = 0; j < num; j++)
			{
				int gift;
				cin >> gift;
				pq.push(gift);
			}
		}
	}
	return 0; 
}
