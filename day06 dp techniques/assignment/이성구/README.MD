
문제 설명: 

n가지 종류의 동전이 있고, 이 동전들의 가치는 모두 각각 다르다. 이 동전들을 사용해서 가치의 합이 k원이 되도록 하자.
1. 순서는 고려하지 않음: 1 2 1 과 2 1 1 이 같음.
2. 사용하지 않거나 중복하는 것 둘다 허용함. 

예제 입력: 맨 앞줄에 n과 k을 입력받고 n줄만큼 동전들의 가치를 입력받음.
3 10
1 
2
5

이들의 방법은 총 10가지 아래와 같다.
5 5
5 2 2 1
5 2 1 1 1
5 1 1 1 1 1
2 2 2 2 2 
2 2 2 2 1 1 
2 2 2 1 1 1 1
2 2 1 1 1 1 1 1
2 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
이제 문제를 다 이해했을거라고 생각 한다.




```C++
int n, k;

int dp[10001];


void solve(int testcase) {
    cin >> n >> k;
    vector<int> v(n);
    for(auto & x: v) cin>>x;
    
    ::memset(dp,0,sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = v[i]; j <= k; j++) {
            if (dp[j - v[i]]) dp[j] += dp[j - v[i]];
        }
    }
    cout << dp[k];
}

int main() {
    fast_io;
    solve(1);
    return 0;
}
```
