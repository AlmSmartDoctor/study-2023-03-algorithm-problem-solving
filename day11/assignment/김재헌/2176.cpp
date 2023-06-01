#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int> > > adj(n);
    while(m--){
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    vector<int> dist(n, 1e9);
    priority_queue<pair<int, int> > pq;
    dist[1] = 0;
    pq.push({0, 1});
    while(pq.size()){
        int d, cur;
        tie(d, cur) = pq.top();
        d *= -1;
        pq.pop();
        if(d > dist[cur]) continue;
        for(auto [nxt, wgt] : adj[cur]){
            if(dist[cur] + wgt < dist[nxt]){
                dist[nxt] = dist[cur] + wgt;
                pq.push({-dist[nxt], nxt});
            }
        }
    }
    vector<int> dp(n, -1);
    function<int(int)> solve = [&](int cur){
        if(cur == 1) return 1;
        int &ret = dp[cur];
        if(ret != -1) return ret;
        ret = 0;
        for(auto [nxt, wgt] : adj[cur]){
            if(dist[cur] > dist[nxt]){
                ret += solve(nxt);
            }
        }
        return ret;
    };
    cout << solve(0);
}
