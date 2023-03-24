//문제 사이트 : https://www.acmicpc.net/problem/1062
//제출 답안 : https://www.acmicpc.net/source/57947802


int ret = 0;

void recursive(int n, int k, int toPick, int checked, int start, vector<int>& words) {

    if (toPick == 0) { // 기저사례 고를수 있는 수가 없는 경우.
        int cnt = 0;
        for (int i = 0; i < n; i++){
            if((words[i] & checked) == words[i])cnt++;
        }
        if(ret < cnt)ret = cnt;
        return;
    }
    
    for (int i = start; i < 26; i++) {
        if (!(checked & (1 << i))) { // 아직 checked 않은 애라면 
            checked |= (1 << i); 
            recursive(n, k, toPick - 1, checked, i,words); // 고르고 재귀
            checked = checked & ~(1 << i); //재귀 끝나면 checked 해제
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> words(n);
    vector<string> antaticaWords(n);
    int i = 0;

    for (auto &antaticaWord: antaticaWords) {
        cin >> antaticaWord; //단어를 입력받기.
        int alphabets = 0;

        for (auto alphabet: antaticaWord)
            alphabets |= 1 << (alphabet - 'a'); // 각 단어 별로 alphabets을 얼마나 갖고있는지 기록.

        words[i++] = alphabets; 
    }
    
    int checked = 0;
    checked |= 1 << ('a' - 'a');
    checked |= 1 << ('n' - 'a');
    checked |= 1 << ('t' - 'a');
    checked |= 1 << ('i' - 'a');
    checked |= 1 << ('c' - 'a');// 기본으로 checked되는 애들.

    if (k < 5) cout<< 0; // 5보다 작으면 무조건 0 a,n,t,i,c가 포함되므로 5이상이여야 함.
    else if (k == 26) cout<< n; // 26이상이면 무조건 모든 case을 적용 가능함.
    else {
        recursive(n, k, k - 5, checked, 0, words); // recursive 시작. 
        cout<<ret;
    }
    
    return 0;
}
