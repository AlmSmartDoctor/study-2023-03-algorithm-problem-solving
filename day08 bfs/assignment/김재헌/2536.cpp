#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int m, n;
    cin >> m >> n;
    int k;
    cin >> k;
    vector<array<int, 4> > v(k);
    for(int i = 0; i < k; i++){
        int b, x1, y1, x2, y2;
        cin >> b >> x1 >> y1 >> x2 >> y2;
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
        v[i] = {x1, y1, x2, y2};
    }
    int sx, sy, dx, dy;
    cin >> sx >> sy >> dx >> dy;
    vector<vector<int> > adj(k + 2);
    for(int i = 0; i < k; i++){
        for(int j = i + 1; j < k; j++){
            if(v[i][2] < v[j][0] || v[i][0] > v[j][2] || v[i][3] < v[j][1] || v[i][1] > v[j][3]) continue;
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }
    for(int i = 0; i < k; i++){
        if(v[i][2] >= sx && v[i][0] <= sx && v[i][3] >= sy && v[i][1] <= sy){
            adj[k].push_back(i);
        }
        if(v[i][2] >= dx && v[i][0] <= dx && v[i][3] >= dy && v[i][1] <= dy){
            adj[i].push_back(k + 1);
        }
    }
    vector<int> dist(k + 2);
    queue<int> q;
    q.push(k);
    while(q.size()){
        int cur = q.front();
        q.pop();
        for(int nxt : adj[cur]){
            if(dist[nxt]) continue;
            dist[nxt] = dist[cur] + 1;
            q.push(nxt);
        }
    }
    cout << dist[k + 1] - 1;
}
