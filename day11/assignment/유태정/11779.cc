#include <bits/stdc++.h>

using namespace std;

#define FAST_IO cin.tie(NULL); ios::sync_with_stdio(false);

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	FAST_IO;
	
	int N, M, src, goal;
	cin >> N >> M;

	vector<pair<int, int>> adj[1001];
	for (int i = 0; i < M; ++i) {
		int u, v, cost;
		cin >> u >> v >> cost;
		adj[u].push_back(make_pair(v, cost));
	}
	cin >> src >> goal;
	
	vector<int> dist(N + 1, numeric_limits<int>::max());
	vector<int> parent(N + 1, -1);
	dist[src] = 0;
	parent[src] = src;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(make_pair(0, src));

	while (!pq.empty()) {
		int cost = pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if(dist[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int length = adj[here][i].second;

			int newCost = cost + length;
			if (newCost < dist[there]) {
				dist[there] = newCost;
				pq.push(make_pair(newCost, there));
				parent[there] = here;
			}
		}
	}

	int currentParent = goal;
	vector<int> path(1, goal);	
	while (currentParent != src) {
		currentParent = parent[currentParent];
		path.push_back(currentParent);
	}

	cout << dist[goal] << "\n" << path.size() << "\n";
	for (auto iter = path.rbegin(); iter != path.rend(); ++iter) {
		cout << *iter << " ";
	}
	cout << "\n";

	return 0;
}