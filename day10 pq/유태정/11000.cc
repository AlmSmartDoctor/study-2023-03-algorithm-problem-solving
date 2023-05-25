// 문제: https://www.acmicpc.net/problem/11000
// 아래 풀이를 참고했습니다.
// https://wooono.tistory.com/393

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO    \
    cin.tie(NULL); \
    ios::sync_with_stdio(false);

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
#endif
    FAST_IO;

    int N;
    cin >> N;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> lectures;
    for (int i = 0; i < N; ++i) {
        int S, T;
        cin >> S >> T;
        lectures.push(make_pair(S, T));
    }

    priority_queue<int, vector<int>, greater<int>> ends;
    ends.push(lectures.top().second);
    lectures.pop();

    while (!lectures.empty()) {
        auto [start, end] = lectures.top();
        lectures.pop();

        ends.push(end);
        if (start >= ends.top()) {
            ends.pop();
        }
    }

    cout << ends.size() << "\n";

    return 0;
}