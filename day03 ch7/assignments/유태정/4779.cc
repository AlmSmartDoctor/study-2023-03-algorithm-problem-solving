#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void solve(vector<char>& line, int left, int right) {
  int length = right - left + 1;
  if (length <= 1) return;

  int mid_left = left + length / 3;
  int mid_right = right - length / 3;

  solve(line, left, mid_left - 1);
  solve(line, mid_right + 1, right);

  for (int i = mid_left; i <= mid_right; ++i) {
    line[i] = ' ';
  }
}

int main() {
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
#endif

  int N;
  while (cin >> N) {
    int total_length = pow(3, N);
    vector<char> line(total_length, '-');
    solve(line, 0, total_length - 1);
    for (auto& c : line) cout << c;
    cout << endl;
  }

  return 0;
}