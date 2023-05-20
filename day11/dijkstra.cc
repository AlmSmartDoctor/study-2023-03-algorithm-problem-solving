#define MAX_V 100
#define INF 987654321

#include <vector>
#include <queue>

using namespace std;

int V;
vector<pair<int, int> > adj[MAX_V];

vector<int> dijkstra(int src) {
    vector<int> dist(V, INF);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int,int> > > pq;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        int cost = pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (dist[here] < cost) continue;

        for (const auto& [there, length] : adj[here]) {
            int nextDist = cost + length;

            if (nextDist < dist[there]) {
                dist[there] = nextDist;
                pq.push(make_pair(nextDist, there));
            }
        }
    }
    return dist;
}