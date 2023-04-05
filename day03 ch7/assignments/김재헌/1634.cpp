#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int k;
    cin >> k;
    int n = 1 << (k - 1);
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    function<int(int, int, int, int)> solve = [&](int l, int r, int tl, int tr) -> int{
        if(l == r) return a[l] == b[tl];
        int amid = (l + r) / 2, bmid = (tl + tr) / 2;
        int ret = solve(l, amid, tl, bmid) + solve(amid + 1, r, bmid + 1, tr);
        ret = max(ret, solve(l, amid, bmid + 1, tr) + solve(amid + 1, r, tl, bmid));
        return ret;
    };
    cout << solve(0, n - 1, 0, n - 1);
}
