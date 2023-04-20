#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int C = 9 * 8 * 7 * 5;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    string p, s;
    cin >> p >> s;
    vector<int> v;
    for(int i = 0; i < s.size(); i++){
        if(s.substr(i, p.size()) == p){
            v.push_back(i + 1);
        }
    }
    vector<vector<int> > dp(v.size(), vector<int>(C, -1));
    function<int(int, int)> solve = [&](int pos, int rem) -> int{
        if(pos == v.size()) return !rem;
        int &ret = dp[pos][rem];
        if(ret != -1) return ret;
        return ret = (solve(pos + 1, rem) + solve(pos + 1, (rem * v[pos]) % C)) % MOD;
    };
    cout << solve(0, 1);
}
