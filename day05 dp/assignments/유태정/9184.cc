// 제출 코드: http://boj.kr/a97e644adf36443dadabfb1509bd5ea4

#include <bits/stdc++.h>

using namespace std;

#define TC(T) int T; cin >> T; while (T--)
#define INPUT(N) int N; cin >> N;
#define FAST_IO cin.tie(NULL); ios::sync_with_stdio(false);

int cache[1001];

int solve(int n) {
	if (n == 1) return 1;
	if (n == 2) return 2;
	if (cache[n]) return cache[n];

	int ans = 1; // "N"
	for (int i = 0; i < n / 2; i++) {
		ans += solve(n / 2 - i);
	}

	cache[n] = ans;
	return ans;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	FAST_IO;
	
	TC(T) {
		INPUT(N);
		cout << solve(N) << endl;
	}

	return 0;
}