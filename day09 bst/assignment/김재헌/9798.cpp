#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<array<int, 3> > v(n);
    for(int i = 0; i < n; i++){
        int k, a;
        cin >> k >> a;
        v[i] = {k, a, i};
    }
    sort(v.begin(), v.end());
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j){
        return v[i][1] < v[j][1];
    });
    set<array<int, 3> > s;  // {key, depth, node}
    vector<array<int, 3> > ans(n, {-1, -1, -1});
    for(int idx : ord){
        if(s.empty()){
            s.insert({v[idx][0], 0, v[idx][2]});
            continue;
        }
        auto it = s.lower_bound({v[idx][0], 0, 0});
        if(it == s.end()){
            auto pit = prev(it);
            ans[(*pit)[2]][2] = v[idx][2];
            ans[v[idx][2]][0] = (*pit)[2];
            s.insert({v[idx][0], (*pit)[1] + 1, v[idx][2]});
        }
        else{
            if(it == s.begin()){
                ans[(*it)[2]][1] = v[idx][2];
                ans[v[idx][2]][0] = (*it)[2];
                s.insert({v[idx][0], (*it)[1] + 1, v[idx][2]});
            }
            else{
                auto pit = prev(it);
                int child = 1;
                if((*pit)[1] > (*it)[1]){
                    swap(pit, it);
                    child = 2;
                }
                ans[(*it)[2]][child] = v[idx][2];
                ans[v[idx][2]][0] = (*it)[2];
                s.insert({v[idx][0], (*it)[1] + 1, v[idx][2]});
            }
        }
    }
    cout << "YES" << '\n';
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 3; j++){
            cout << ans[i][j] + 1 << ' ';
        }
        cout << '\n';
    }
}
