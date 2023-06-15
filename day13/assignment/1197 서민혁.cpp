#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> parent;
class bigger
{
    public:
    bool operator() (vector<ll> a, vector<ll> b)
    {
        return a[2] > b[2];
    }
};

ll getParent(ll node)
{
    return (parent[node] == node ? node : getParent(parent[node]));
}

void merge(ll node1, ll node2)
{
	parent[node1] = getParent(node1);
	parent[node2] = getParent(node2);

	if (parent[node1] < parent[node2]) 
        parent[parent[node2]] = node1;
	else 
        parent[parent[node1]] = node2;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int V, E;
    cin >> V >> E;
    parent.resize(V + 1);
    for (int i = 1; i <= V; i++)
    {
        parent[i] = i;
    }

    ll sum = 0;

    priority_queue<vector<ll>, vector<vector<ll>>, bigger> edges;

    for (int i = 0; i < E; i++)
    {
        ll node1, node2, weight;
        cin >> node1 >> node2 >> weight;
        vector<ll> edge = vector<ll> {node1, node2, weight};
        edges.push(edge);
    }

    // while (!edges.empty())
    // {
    //     cout << edges.top()[0] << ", " << edges.top()[1] << ", " << edges.top()[2] << "\n";
    //     edges.pop();
    // }

    while (!edges.empty())
    {
        vector<ll> edge = edges.top();
        edges.pop();
        if (getParent(edge[0]) != getParent(edge[1]))
        {
            sum += edge[2];
            merge(edge[0], edge[1]);
        }
    }
    cout << sum;

}
