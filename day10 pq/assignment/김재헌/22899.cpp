#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<vector<int> > v(n);
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        x--;
        v[x].push_back(i);
    }
    vector<int> b(n);
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < v[i].size(); j++){
            v[i][j] = b[v[i][j]];
        }
        sort(v[i].rbegin(), v[i].rend());
    }
    vector<int> p;
    for(int i = 0; i < n; i++){
        if(v[i].size()){
            p.push_back(i);
        }
    }
    priority_queue<int> pq;
    ll sum = 0;
    for(int l = 1; l <= n; l++){
        vector<int> np;
        for(int u : p){
            int x = v[u].back();
            v[u].pop_back();
            if(v[u].size()){
                np.push_back(u);
            }
            if(pq.size() == k && pq.top() <= x) continue;
            sum += x;
            if(pq.size() == k){
                sum -= pq.top();
                pq.pop();
            }
            pq.push(x);
        }
        cout << (pq.size() < k ? -1 : sum) << ' ';
        p = np;
    }
}
