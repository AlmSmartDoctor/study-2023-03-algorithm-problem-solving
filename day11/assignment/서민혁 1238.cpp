#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


vector<vector<pair<int, int>>> routes;
int V, E;

vector<ll> dijkstra(int start)
{
    vector<ll> distance = vector<ll>(V, numeric_limits<ll>::max());
    priority_queue<pair<int, int>, vector<pair<int, int>>, less<>> q;
    distance[start] = 0;
    q.push(pair<int, int> {0, start});
    while (!q.empty())
    {
        int current_position = q.top().second;
        int current_distance = -q.top().first;
        q.pop();

        if (distance[current_position] < current_distance)
            continue;

        for (int i = 0; i < routes[current_position].size(); i++)
        {
            int dist = routes[current_position][i].second + current_distance;
            if (dist < distance[routes[current_position][i].first])
            {
                distance[routes[current_position][i].first] = dist;
                q.push(pair<int, int> {-dist, routes[current_position][i].first});
            }
        }
    }
    return distance;
}


int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int X;
    cin >> V >> E >> X;
    routes.resize(V);
    for (int i = 0; i < E; i++)
    {
        int start, end, length;
        cin >> start >> end >> length;
        routes[start - 1].push_back(pair<int, int> {end - 1, length});
    }

    vector<vector<ll>> distance_matrix(V);
    for (int i = 0; i < V; i++)
    {
        distance_matrix[i] = dijkstra(i);
    }
    
    // for (int i = 0; i < V; i++)
    // {
    //     for (int j = 0; j < V; j++)
    //     {
    //         cout << distance_matrix[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    ll maximum = -1;
    for (int i = 0; i < V; i++)
    {
        maximum = max(maximum, distance_matrix[i][X - 1] + distance_matrix[X - 1][i]);
    }
    cout << maximum;
}
