// 답안 참고: https://algwang.tistory.com/10
// 제출 코드: http://boj.kr/d7497df0ed62424f922d603cbd2ed472

#include <iostream>
#include <map>
#include <vector>

using namespace std;

int N, s[100000], e[100000];

int main() {
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
#endif
  ios_base ::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  // 입력
  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> s[i] >> e[i];
  }

  // N이 1인 경우
  if (N == 1) {
    cout << 0 << '\n';
    cout << s[0] << '\n';
    return 0;
  }

  int sum = 0;
  vector<int> history;

  // 첫 스트레스 위치 찾기
  int start = s[0];
  int end = e[0];
  int index = 1;
  while (index < N) {
    // 현재 구간이 기존 구간보다 뒤에 떨어져 있는 경우
    //         |-----|
    // |-----|
    //       ^
    if (s[index] > end) {
      history = vector<int>(index, end);
      break;
    }
    // 현재 구간이 기존 구간보다 앞에 떨어져 있는 경우
    // |-----|
    //         |-----|
    //         ^
    else if (e[index] < start) {
      history = vector<int>(index, start);
      break;
    }
    // 현재 구간이 기존 구간에 포함되는 경우
    //   |-----|
    // |----------|
    //   ^     ^
    else if (start <= s[index] && e[index] <= end) {
      start = s[index];
      end = e[index];
    }
    // 현재 구간이 기존 구간의 뒤쪽으로 겹치는 경우
    //     |-----|
    // |-----|
    // ^   ^
    else if (start <= s[index] && s[index] <= end && e[index] > end) {
      start = s[index];
    }
    // 현재 구간이 기존 구간의 앞쪽으로 겹치는 경우
    // |-----|
    //     |-----|
    //       ^   ^
    else if (start <= e[index] && e[index] <= end && s[index] < start) {
      end = e[index];
    }

    index += 1;
  }

  // 끝까지 돈 경우 스트레스는 변하지 않습니다.
  if (index == N) {
    history = vector<int>(N, start);
  }

  // 남은 프링글스에 대해서 구간을 계산합니다.
  for (int i = index; i < N; ++i) {
    int last = history.back(); // 직전 스트레스

    // 직전 스트레스가 현재 구간에 속하는 경우
    if (s[i] <= last && last <= e[i]) {
      history.push_back(last);
    }
    // 직전 스트레스가 현재 구간보다 앞에 있는 경우
    else if (last < s[i]) {
      sum += s[i] - last;
      history.push_back(s[i]);
    }
    // 직전 스트레스가 현재 구간보다 뒤에 있는 경우
    else {
      sum += last - e[i];
      history.push_back(e[i]);
    }
  }

  // 결과 출력
  cout << sum << '\n';
  for (const auto& el : history) {
    cout << el << '\n';
  }

  return 0;
}