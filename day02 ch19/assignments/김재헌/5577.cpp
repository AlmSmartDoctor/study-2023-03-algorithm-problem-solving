#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    auto solve = [&](vector<int> &t){
        t.push_back(4);
        stack<pair<int, int> > stk;
        int ret = n;
        for(int i = 0; i < n + 1; i++){
            if(stk.empty() || stk.top().first != v[i]){
                if(stk.size() && stk.top().second >= 4){
                    ret -= stk.top().second;
                    stk.pop();
                    i--;
                }
                else stk.push({v[i], 1});
            }
            else stk.top().second++;
        }
        return ret;
    };
    int ans = n;
    for(int i = 0; i < n; i++){
        if(i - 3 >= 0 && v[i - 3] == v[i - 2] && v[i - 2] == v[i - 1]){
            int tmp = v[i];
            v[i] = v[i - 1];
            ans = min(ans, solve(v));
            v[i] = tmp;
        }
        if(i + 3 < n && v[i + 1] == v[i + 2] && v[i + 2] == v[i + 3]){
            int tmp = v[i];
            v[i] = v[i + 1];
            ans = min(ans, solve(v));
            v[i] = tmp;
        }
        if(i - 1 >= 0 && i + 2 < n && v[i - 1] == v[i + 1] && v[i + 1] == v[i + 2]){
            int tmp = v[i];
            v[i] = v[i - 1];
            ans = min(ans, solve(v));
            v[i] = tmp;
        }
        if(i - 2 >= 0 && i + 1 < n && v[i - 2] == v[i - 1] && v[i - 1] == v[i + 1]){
            int tmp = v[i];
            v[i] = v[i - 1];
            ans = min(ans, solve(v));
            v[i] = tmp;
        }
    }
    cout << ans;
}
