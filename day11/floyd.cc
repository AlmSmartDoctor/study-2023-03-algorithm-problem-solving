#define MAX_V 100
#define INF 987654321

#include <vector>

using namespace std;

int V;
int adj[MAX_V][MAX_V];

void floyd() {
    for (int i = 0; i < V; ++i) adj[i][i] = 0;

    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}