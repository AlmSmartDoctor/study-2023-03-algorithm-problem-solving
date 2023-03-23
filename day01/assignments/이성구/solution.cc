//문제 사이트 : https://www.acmicpc.net/problem/1062
//제출 답안 : https://www.acmicpc.net/source/57947802


int ret = 0;

void recursive(int n, int k, int toPick, int checked, int start,vector<int>& words) {

    if (toPick == 0) {
        int cnt = 0;
        for (int i = 0; i < n; i++){
            if((words[i] & checked) == words[i])cnt++;
        }
        if(ret < cnt)ret = cnt;
        return;
    }
    for (int i = start; i < 26; i++) {
        if (!(checked & (1 << i))) {
            checked |= (1 << i);
            recursive(n, k, toPick - 1, checked, i,words);
            checked = checked & ~(1 << i);
        }
    }

}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> words(n);
    vector<string> antaticaWords(n);
    int cnt = 5, i = 0;

    for (auto &antaticaWord: antaticaWords) {
        cin >> antaticaWord;
        int alphabets = 0;

        for (auto alphabet: antaticaWord)
            alphabets |= 1 << (alphabet - 'a');

        words[i++] = alphabets;
    }
    int checked = 0;
    checked |= 1 << ('a' - 'a');
    checked |= 1 << ('n' - 'a');
    checked |= 1 << ('t' - 'a');
    checked |= 1 << ('i' - 'a');
    checked |= 1 << ('c' - 'a');

    if (k < 5) cout<< 0;
    else if (k == 26) cout<< n;
    else {
        recursive(n, k, k - 5, checked, 0,words);
        cout<<ret;
    }
}
