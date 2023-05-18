#include <iostream>
#include <set>

using namespace std;

int T, K, N;
char C;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> T;
  while (T--) {
    multiset<int> container;

    cin >> K;
    while (K--) {
      cin >> C >> N;
      switch (C) {
        case 'D':
          if (container.empty()) break;
          if (N == -1) {
            container.erase(container.begin());
          } else {
            container.erase(--container.end());
          }
          break;
        case 'I':
          container.insert(N);
          break;
      }
    }

    if (container.empty()) {
      cout << "EMPTY\n";
    } else {
      cout << *container.rbegin() << " " << *container.begin() << "\n";
    }
  }

  return 0;
}