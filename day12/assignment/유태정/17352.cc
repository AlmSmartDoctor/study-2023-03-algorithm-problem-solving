#include <iostream>
#include <vector>

using namespace std;

int parent[300001];
int height[300001];

int find(int u) {
  if (u == parent[u]) return u;
  return parent[u] = find(parent[u]);
}

void merge(int u, int v) {
  u = find(u);
  v = find(v);
  if (u == v) return;
  if (height[u] > height[v]) swap(u, v);
  parent[u] = v;
  if (height[u] == height[v]) ++height[v];
}

int main() {
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
#endif
  int N;
  cin >> N;

  for (int i = 0; i < 300000; i++) {
    parent[i] = i;
  }

  for (int i = 0; i < N - 2; i++) {
    int u, v;
    cin >> u >> v;
    merge(u, v);
  }

  vector<int> roots;
  for (int i = 1; i <= N; i++) {
    if (i == parent[i]) roots.push_back(i);
  }
  cout << roots[0] << ' ' << roots[1] << endl;

  return 0;
}