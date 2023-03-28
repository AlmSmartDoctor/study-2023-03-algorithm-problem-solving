//https://www.acmicpc.net/problem/25096 

/*
 * 문제 설명 : 입력으로 테스트케이스와 각각의 테스트케이스에 N과 N개의 숫자(D1....Dn)를 입력받는다.
 * N은 핫케이크의 개수를 의미하고 각각의 D는 핫케이크들의 맛 정도를 의미한다. 
 *
 * 규칙1 :고객들은 이전 고객보다 맛있거나 동일하게 맛있는 경우에만 값을 지불한다. 맛있다는건 D의 값이 크다는 것. 
 * 규칙2 :첫번째 고객은 당연히 값을 지불한다.
 * 규칙3 :핫케이크들은 deque로 제공이 되며 앞뒤로만 고객들에게 팔수가 있다.
 *
 * 답 : 고객들이 지불을 최대한 많이 하게 하는것이 목표. 지불한 최대개수를 구하여라.
*/

#include<bits/stdc++.h>

using namespace std;
#define endl '\n'
#define fast_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

void solve(int testcase) {
    int n, ans = 0;
    cin >> n;
    deque<int> dq;


    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        dq.push_back(x);
    }

    int latestMaxValue = 0;

    for (int i = 0; i < n; i++) {
        
        if (dq.front() > dq.back()) {
            if (dq.back() >= latestMaxValue)ans++;
            latestMaxValue = max(latestMaxValue, dq.back());
            dq.pop_back();
        } 
        
        else {
            if (dq.front() >= latestMaxValue)ans++;
            latestMaxValue = max(latestMaxValue, dq.front());
            dq.pop_front();
        }
    }

    cout << "Case #" << testcase + 1 << ": " << ans << endl;

}

int main() {
    fast_io;
    int t;
    cin >> t;
    for(int i = 0,i < t; i++)
        solve(i);
    return 0;
}



