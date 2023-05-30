// 출처: https://www.acmicpc.net/problem/14221

#define MAX_V 5001
#define INF 987654321

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int V, E;
vector<pair<int, int> > adj[MAX_V]; // 인접 리스트

vector<int> dijkstra(int src) {
    // src 부터 나머지 정점들로의 거리를 저장하는 배열
    vector<int> dist(V + 1, INF);
    dist[src] = 0;

    // cout << "src: " << src << endl;

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int,int> > > pq;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        int cost = pq.top().first;
        int here = pq.top().second;
        pq.pop();

        // 이미 계산된 거리가 더 최적이면 스킵
        if (dist[here] < cost) continue;

        // 현재 정점에서 연결된 다른 정점들을 검사
        for (const auto& edge : adj[here]) {
            int there = edge.first;
            int length = edge.second;
            int nextDist = cost + length;

            // 현재 계산된 새로운 거리가 더 가까우면 거리를 갱신하고 큐에 추가
            if (nextDist < dist[there]) {
                dist[there] = nextDist;
                pq.push(make_pair(nextDist, there));
            }
        }
    }

    // for(int i = 1; i < V+1; i++) {
    //     cout << dist[i] << " ";
    // }
    // cout << endl;

    return dist;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    freopen("input.txt", "r", stdin);
    cin >> V >> E;

    int a, b, c;
    for (int i = 0; i < E; i++) {
        cin >> a >> b >> c;
        adj[a].push_back(make_pair(b, c));
        adj[b].push_back(make_pair(a, c));
    }

    int home, dest;
    cin >> home >> dest;

    vector<int> homes, dests;
    int n;
    
    for (int i = 0; i < home; i++) {
        cin >> n;
        homes.push_back(n);
    }
    for (int i = 0; i < dest; i++) {
        cin >> n;
        dests.push_back(n);
    }

    int minDist = INF, minHome;

    for (int i = 0; i < home; i++) {
        vector<int> dist = dijkstra(homes[i]);
        for (int j = 0; j < dest; j++) {
            if (dist[dests[j]] < minDist) {
                minDist = dist[dests[j]];
                minHome = homes[i];
            }
        }
    }

    cout << minHome;

    return 0;
}