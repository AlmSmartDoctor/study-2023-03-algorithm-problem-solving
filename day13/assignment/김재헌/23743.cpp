#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

struct Myset{
    vector<int> p;

    Myset(int n){
        p.resize(n, -1);
    }

    int find(int x){
        if(p[x] < 0) return x;
        return p[x] = find(p[x]);
    }

    void merge(int u, int v){
        u = find(u);
        v = find(v);
        if(u == v) return;
        if(p[u] < p[v]){
            p[u] += p[v];
            p[v] = u;
        }
        else{
            p[v] += p[u];
            p[u] = v;
        }
    }
};

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<array<int, 3> > e;
    while(m--){
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        e.push_back({c, a, b});
    }
    for(int i = 0; i < n; i++){
        int t;
        cin >> t;
        e.push_back({t, i, n});
    }
    sort(e.begin(), e.end());
    int ans = 0;
    Myset ms(n + 1);
    for(auto [c, a, b] : e){
        if(ms.find(a) == ms.find(b)) continue;
        ms.merge(a, b);
        ans += c;
    }
    cout << ans;
}
