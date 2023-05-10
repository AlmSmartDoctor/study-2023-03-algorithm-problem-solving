#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<int> relations[2000];
bool visited[2000];

bool doesFifthDepthRelationExist(int here, int depth) {
  if (depth >= 4) {
    return true;
  }

  for (auto& there : relations[here]) {
    if (!visited[there]) {
      visited[there] = true;
      bool doesExist = doesFifthDepthRelationExist(there, depth + 1);
      visited[there] = false;

      if (doesExist) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  cin >> N >> M;
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    relations[a].push_back(b);
    relations[b].push_back(a);
  }

  for (int here = 0; here < N; here++) {
    visited[here] = true;
    bool doesExist = doesFifthDepthRelationExist(here, 0);
    visited[here] = false;

    if (doesExist) {
      cout << 1 << endl;
      return 0;
    }
  }

  cout << 0 << endl;

  return 0;
}