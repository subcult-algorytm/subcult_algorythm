#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <deque>

using namespace std;
int T;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;

	while (T--) {
		int N;
		cin >> N;
		vector<int> v1(N);

		for (int y = 0; y < N; ++y) {
			cin >> v1[y];
		}
		sort(v1.begin(), v1.end());
		int ans = 0;

		deque<int> dq;
		for (int y = N - 1; y >= 0; --y) {
			if (y & 1) dq.push_back(v1[y]);
			else dq.push_front(v1[y]);
		}

		int sz = dq.size();

		for (int idx = 0; idx <= sz; ++idx) {
			int cur = idx % sz;
			int next = (idx + 1) % sz;
			ans = max(ans, abs(dq[cur] - dq[next]));
		}
		cout << ans << "\n";
	}
	return 0;
}