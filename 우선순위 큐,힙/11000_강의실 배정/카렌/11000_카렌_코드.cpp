#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	
	//pair를 쓰면 sort를 사용 할 시에 첫 번째 원소 (시작 시간)을 기준으로 자동 정렬 된다.
	
	vector<pair<int,int>> lectures(N);
	
	for(int i = 0; i <  N; i++)
	{
		cin >> lectures[i].first >> lectures[i].second;
	}
	
	// 1. 모든 수업 시작 시간 (S)를 기준으로 오름차순 정렬
	
	sort(lectures.begin(),lectures.end());
	
	// 2. 최소힙 선언(종료시간)
	
	priority_queue<int,vector<int>,greater<int>> pq;
	 
	pq.push(lectures[0].second); // 강의실 하나 배정 
	
	// 3. 두 번째 수업부터 순회하며 배정
	
	for(int i = 1; i < N; i++)
	{
		
		if(lectures[i].first >= pq.top())
		{
			pq.pop();
		}
		
		pq.push(lectures[i].second);
	}
	

	// 4. 정답 출력 : 큐의 크기 == 필요한 최소 강의실 갯수 
	
	cout << pq.size() << "\n"; 
	 
}
