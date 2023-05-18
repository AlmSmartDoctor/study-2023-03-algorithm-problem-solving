#include <iostream>
#include <map>

using namespace std;

int T, K, N;
char C;

int main() {
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(false);

  cin >> T;
  while (T--) {
    map<int, int> container;

    cin >> K;
    while (K--) {
      cin >> C >> N;

      switch (C) {
        case 'D':
          if (container.empty()) break;
          if (N == -1) {
            if ((*container.begin()).second == 1) {
              container.erase(container.begin());
            } else {
              (*container.begin()).second--;
            }
          } else {
            if ((*container.rbegin()).second == 1) {
              container.erase(--container.end());
            } else {
              (*container.rbegin()).second--;
            }
          }
          break;
        case 'I':
          if (container.find(N) == container.end()) {
            container.insert(make_pair(N, 1));
          } else {
            container[N]++;
          }
          break;
      }
    }

    if (container.empty()) {
      cout << "EMPTY\n";
    } else {
      cout << (*container.rbegin()).first << " " << (*container.begin()).first << "\n";
    }
  }

  return 0;
}