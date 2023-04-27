#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

int dp[51][1001];

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    for(int i = 1; i <= 1000; i++){
        dp[0][i] = 1e9;
    }
    for(int i = 1; i <= 50; i++){
        for(int j = 1; j <= 1000; j++){
            dp[i][j] = 1e9;
            for(int k = 1; k <= j; k++){
                dp[i][j] = min(dp[i][j], 1 + max(dp[i - 1][k - 1], dp[i][j - k]));
            }
        }
    }
    int tt;
    cin >> tt;
    while(tt--){
        int b, m;
        cin >> b >> m;
        cout << dp[b][m] << '\n';
    }
}
