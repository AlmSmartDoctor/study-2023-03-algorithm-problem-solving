static const int INITIAL_VALUE = -99999;

void solve(int testcase) {
    int n;
    cin>>n;
    vector<int> indent(n);
    vector<int> goal(n);

    for (int i = 0; i < n; i++) {
        cin >> indent[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> goal[i];
        goal[i] -= indent[i];
    }

    int ans = 0;
    int maxValue = INITIAL_VALUE;

    if(n == 0){
        cout<< 0;
        return;
    }

    if(n == 1){
        cout<< abs(goal[0]);
        return;
    }

    for (auto cur: goal) {
        if (maxValue == INITIAL_VALUE){
            maxValue = cur;
        }
        else if (maxValue < 0) {
            if (cur < 0) {
                maxValue = -max(-maxValue, -cur);
            }
            if (cur >= 0) {
                ans += -maxValue;
                maxValue = cur;
            }
        }
        else {
            if (cur <= 0) {
                ans += maxValue;
                maxValue = cur;
            }
            if (cur > 0) {
                maxValue = max(maxValue,cur);
            }
        }
    }
    ans += abs(maxValue);

    cout << ans;

}
