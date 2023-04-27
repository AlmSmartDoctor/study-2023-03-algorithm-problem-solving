#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


vector<vector<int>> dp(201, vector<int>(101, -1));
ll biggest = 2100000000;

int combination(int a, int b)
{
    if (dp[a][b] == -1)
    {
        b = min(b, a - b);
        if (b == 0)
        {
            dp[a][b] = 1;
            return dp[a][b];
        }
        else
        {
            ll include = combination(a - 1, b - 1);
            ll exclude = combination(a - 1, b);
            if (include + exclude > biggest)
            {
                dp[a][b] = -2;
                return 2100000000;
            }
            else
            {
                dp[a][b] = combination(a - 1, b - 1) + combination(a - 1, b);
                return dp[a][b];
            }
        }
    }
    else if (dp[a][b] == -2)
    {
        return 2100000000;
    }
    else
    {
        return dp[a][b];
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, M, K;
    cin >> N >> M >> K;
    if (combination(N + M, M) < K)
    {
        cout << -1;
    }
    else
    {
        int NM = N + M;
        int skipped = 0;
        for (int i = 0; i < NM; i++)
        {
            if (N * M == 0) break;
            if (K - skipped <= combination(N + M - 1, M))
            {
                cout << "a";
                N -= 1;
            }
            else
            {
                cout << "z";
                skipped += combination(N + M - 1, M);
                M -= 1;
            }
        }
        for (int i = 0; i < N; i++) cout << "a";
        for (int i = 0; i < M; i++) cout << "z";
    }
}
