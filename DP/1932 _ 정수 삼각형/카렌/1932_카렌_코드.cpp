#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	vector<vector<int>> triangle(n, vector<int>(n, 0));
	vector<vector<int>> dp(n, vector<int>(n, 0));
	
	// 1. 삼각형 입력 받기
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= i; j++){
			cin >> triangle[i][j];
		}
	}
	
	// 2. 초기값 설정 (피라미드 꼭대기)
	dp[0][0] = triangle[0][0];
	
	// 3. 점화식을 이용해 DP 채우기
	for(int i = 1; i < n; i++){
		for(int j = 0; j <= i; j++){
			// 케이스 1 : 맨 왼쪽 끝 인 경우 (오른쪽 위에서만 내려 올 수 있다)
			if(j == 0){
				dp[i][j] = dp[i-1][j] + triangle[i][j];
			} 
			// 케이스 2 : 맨 오른쪽 끝인 경우 (왼쪽 위에서만 내려 올 수 있음)
			else if(j == i){
				dp[i][j] = dp[i-1][j-1] + triangle[i][j]; //
			} 
			// 케이스 3 : 중간에 있는 경우 (양쪽 위 모두에서 내려 올 수 있다)
			else { 
				dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]) + triangle[i][j]; 
			}
		}
	} 
	

	// 4. 정답 찾기 (맨 마지막 줄에서 최댓값 찾기)
	int max_score = 0;

	for(int j = 0; j < n; j++){
		max_score = max(max_score, dp[n-1][j]);
	}

	cout << max_score << "\n";

	return 0; 
} 
