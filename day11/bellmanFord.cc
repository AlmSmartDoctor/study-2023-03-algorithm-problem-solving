#define MAX_V 100
#define INF 987654321

#include <queue>
#include <vector>

using namespace std;

int V;
vector<pair<int, int> > adj[MAX_V];

vector<int> bellmanFord(int src) {
    vector<int> upper(V, INF);
    upper[src] = 0;

    bool updated;
    for (int iter = 0; iter < V; ++iter) {
        updated = false;

        for (int here = 0; here < V; ++here) {
            for (const auto& [there, cost] : adj[here]) {
                if (upper[here] != INF && upper[there] > upper[here] + cost) {
                    upper[there] = upper[here] + cost;
                    updated = true;
                }
            }
        }

        if (!updated) break;
    }

    if (updated) upper.clear();

    return upper;
}