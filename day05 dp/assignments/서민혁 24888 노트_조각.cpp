#include <string>
#include <iomanip>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <queue>
using namespace std;
typedef long long ll;
// https://burningfalls.github.io/algorithm/boj-24888/ 참고
int N, M;
vector<vector<pair<int, ll>>> routes;  
vector<ll> time_spent;
vector<int> picked_up;
vector<int> essential;
vector<int> best_route;
void dijkstra()
{
    // time_spent is shortest time_spent from node 1 to node i
    // routes[i] is a vector of vectors representing each edge starting from i
    // picked_up[i] is maximum number of note pieces picked up at node i
    priority_queue<pair<ll, int>> q;
    time_spent[1] = 0;
    picked_up[1] = essential[1];
    q.push(pair<ll, int> {0, 1});

    while (!q.empty())
    {
        ll current_time_spent = -q.top().first;
        int current_position = q.top().second;
        q.pop();

        // if this route is already inferior, there is no need to go any deeper
        if (time_spent[current_position] < current_time_spent)
            continue;

        // check every routes passing current position
        for (int i = 0; i < routes[current_position].size(); i++)
        {
            // current_time means time spent while traveling the route passing the current position and ends at destination
            ll current_time = routes[current_position][i].second + current_time_spent;
            int destination = routes[current_position][i].first;

            // no need to check further if taking this route is not optimal
            // since we have to check all the possible shortest routes, we must be inclusive
            if (current_time <= time_spent[destination])
            {
                // since a new shortest route has been found, change the time_spent value
                // we have to check the routes branching from destination again since a shorter route has been found
                if (current_time < time_spent[destination])
                {
                    time_spent[destination] = current_time;
                    q.push(pair<ll, int> {-current_time, destination});
                }

                // if there is a way to pick up more pieces than update the number of picked up pieces
                if (picked_up[destination] < picked_up[current_position] + essential[destination])
                    picked_up[destination] = picked_up[current_position] + essential[destination];
            }
        }
    }
}

// finding the node we were at before current position
void backtrace(int current_position)
{
    // when the route is complete, print the route and exit
    if (current_position == 1)
    {
        cout << best_route.size() << "\n";
        for (int i = best_route.size() - 1; i >= 0; i--)
        {
            cout << best_route[i] << " ";
        }
        exit(0);
    }

    // if the route is incomplete enumerate through all the routes and check which route fits the criteria
    for (int i = 0; i < routes[current_position].size(); i++)
    {
        int destination = routes[current_position][i].first;
        ll travel_time = routes[current_position][i].second;
        
        // note that since we are going backwards, time_spent[destination] < time_spent[current_position]
        // if time_spent is minimum and the picked_up is maximum, that is the ideal route
        // when a ideal route has been found, go deeper and check
        if (
            travel_time + time_spent[destination] == time_spent[current_position] &&
            picked_up[destination] + essential[current_position] == picked_up[current_position]
        )
        {
            best_route.push_back(destination);
            backtrace(destination);
            best_route.pop_back();
        }
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;  
    routes.resize(N + 1);
    time_spent.resize(N + 1);
    picked_up.resize(N + 1);
    essential.resize(N + 1);
    for (int i = 0; i < M; i++)
    {
        int start, end;
        ll length;
        cin >> start >> end >> length;
        routes[start].push_back(pair<int, ll> {end, length});
        routes[end].push_back(pair<int, ll> {start, length});
    }

    int essential_node_count = 0;
    for (int i = 1; i <= N; i++)
    {
        time_spent[i] = numeric_limits<ll>::max();
        picked_up[i] = -1;
        cin >> essential[i];
        if (essential[i] == 1) essential_node_count++;
    }
    
    dijkstra();
    if (picked_up[N] == essential_node_count)
    {
        best_route.push_back(N);
        backtrace(N);
    }
    else
    {
        cout << -1;
    }
}
