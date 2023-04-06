#include <algorithm>
#include <iostream>
#include <vector>

#define VVC vector<vector<char>>
#define VC vector<char>

using namespace std;

void solve(VVC& canvas, int top, int left, int bottom, int right) {
  int length = bottom - top + 1;
  if (length <= 1) return;

  int mid_top = top + length / 3;
  int mid_bottom = bottom - length / 3;
  int mid_left = left + length / 3;
  int mid_right = right - length / 3;

  for (int i = mid_top; i <= mid_bottom; ++i) {
    for (int j = mid_left; j <= mid_right; ++j) {
      canvas[i][j] = ' ';
    }
  }

  solve(canvas, top, left, top + length / 3 - 1, left + length / 3 - 1);

  for (int r = top; r < bottom; r += length / 3) {
    for (int c = left; c < right; c += length / 3) {
      if (r == mid_top && c == mid_left) {
        continue;
      } else if (r == top && c == left) {
        continue;
      } else {
        for (int i = 0; i < length / 3; ++i) {
          for (int j = 0; j < length / 3; ++j) {
            canvas[r + i][c + j] = canvas[top + i][left + j];
          }
        }
      }
    }
  }
}

int main() {
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
#endif

  int N;
  cin >> N;

  VVC canvas(N, VC(N, '*'));

  solve(canvas, 0, 0, N - 1, N - 1);

  for (auto& line : canvas) {
    for (auto& c : line) {
      cout << c;
    }
    cout << endl;
  }
  cout << endl;

  return 0;
}