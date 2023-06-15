#include <cmath>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int parent[100];

int findParent(int node) {
  if (parent[node] == node) return node;
  return findParent(parent[node]);
}

void unionParent(int node1, int node2) {
  node1 = findParent(node1);
  node2 = findParent(node2);
  if (node1 < node2)
    parent[node2] = node1;
  else
    parent[node1] = node2;
}

bool isCycle(int node1, int node2) {
  node1 = findParent(node1);
  node2 = findParent(node2);
  if (node1 == node2)
    return true;
  else
    return false;
}

int main() {
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
#endif
  int N;
  cin >> N;

  // 입력 처리`
  vector<pair<double, double> > vertecies;
  for (int i = 0; i < N; i++) {
    double x, y;
    cin >> x >> y;
    vertecies.emplace_back(x, y);
  }

  // 거리 계산
  priority_queue<tuple<double, int, int>, vector<tuple<double, int, int> >, greater<tuple<double, int, int> > > edges;
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      double cost = sqrt(pow(vertecies[i].first - vertecies[j].first, 2) + pow(vertecies[i].second - vertecies[j].second, 2));
      edges.emplace(cost, i, j);
      edges.emplace(cost, j, i);
    }
  }

  // 집합 초기화
  for (int i = 0; i < N; i++) {
    parent[i] = i;
  }

  // 간선 순회
  double totalCost = 0;
  while (!edges.empty()) {
    auto [cost, from, to] = edges.top();
    edges.pop();

    if (!isCycle(from, to)) {
      totalCost += cost;
      unionParent(from, to);
    }
  }

  // 정답 출력
  cout << totalCost << endl;

  return 0;
}