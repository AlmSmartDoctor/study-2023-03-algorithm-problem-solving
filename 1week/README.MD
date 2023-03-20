##무식하게 풀기(Brute Force)
-------------------------------------
이번 챕터에서 배울 알고르짐은 완전 탐색 알고리즘(Brute force) 입니다. 


Brute Force는 가능한 경우의 수를 일일이 나열하면서 CPU의 성능을 통해 답을 찾는 방법입니다.

모든 방법을 다 탐색하므로 무식하다는 표현이 들어갔다고 합니다.

### 재귀호출과 완전 탐색
-------------------------------------

완전 탐색의 기초적인 기법들을 살펴 봅시다.

##### 재귀호출
완전 탐색 문제들은 범위를 좁혀보면 작게 쪼갤 수 있는 경우가 많습니다. 
이런 경우, 아래의 코드처럼 재귀를 사용하여 풀 수 있습니다. 

```C++
// 둘다 1부터 n까지 더하는 함수.
int sum(int n){
    int ret = 0;
    for(int i = 0; i<= n; i++){
        ret += i
    }
    return ret;
}

int recursiveSum(int n) {
    if(n == 1) return 1;
    return n + recursiveSum(n-1);
}
//모든 재귀 함수는 더이상 쪼개지지 않는 단위인 base case(기저 사례)을 조건문으로 갖고 있어야 합니다.
```

##### 중첩 반복문 대체하기
---------------------------------------
0번 부터 차례대로 번호가 매겨진 n개의 원소 중 4개를 고르는 모든 경우를 출력하는 코드를 봐보자.

```C
for(int i = 0; i< n; i++)
    for(int j = i+1; i< n; i++)
        for(int k = j+1; i< n; i++)
            for(int l = l+1; i< n; i++)
                cout<< i << " " << j << " " << k << " " << l <<endl
```

이런 식의 반복문을 작성하는 건 복잡하고 유연하지 못합니다.
아래의 코드처럼 재귀를 사용하여 리팩토링이 가능합니다.


```C
// picked: 지금까지 고른 원소들
// toPick: 더 고를 원소의 수
// 앞으로 toPick개의 원소를 고르는 모든 방법을 출력한다.
void pick(int n, vector<int>& picked, int toPick) {
    if(toPick == 0) {printPicked(picked); return;}
    
    // 고를 수 있는 가장 작은 번호
    int smallest  = picked.empty() ? 0: picked.back() + 1

    for(int next = smallest; next < n; ++next){
        picked.push_back(next);
        pick(n,picked,toPick-1);
        picked.pop_back();
    }
}
```
다음의 재귀는 n개중에 몇개를 고를지를 정할 수 있다는 장점이 있습니다.

#### 예제 : 보글 게임
-------------------------------------
(책 150p)

대충 5*5 알파벳 격자판에서 특정 단어들을 인식해서 찾는 문제입니다. (대각선 허용)

base case(기저 사례)의 조건들을 먼저 정해 봅시다.
1. 좌표에 있는 글자가 원하는 단어의 첫 글자가 아닌 경우 항상 실패
2. (1번이 아닌 경우)원하는 단어가 한 글자인 경우 항상 성공

좌표계의 범위에서 벗어난 경우도 예외처리를 해야합니다.

코드를 한번 봅시다. 
```C++
const int dx[8] = {-1,-1-1,1,1,1,0,0}
const int dy[8] = {-1,0,1,-1,0,1,-1,1}
//마찬가지로 재귀 함수. 이미 단어의 첫글자를 찾은 상태라고 가정합시다.

bool hasWord(int y, int x, const string& word) {
    if(!inRange(y,x))return false; // 범위 밖인 경우
    if(board[y][x] != word[0]) return false; // 원하는 단어의 첫글자가 아닌 경우
    if(word.size() == 1)return true; // 원하는 단어가 한글자인 경우 성공!

    for(int direction = 0; direction < 8; ++direction){
        int nextY = y + dy[direction], nextX = x + dx[direction];
        if(hasWord[nextY, nextX, word.substr(1)])
            return true;
    }
    return false
}
```
단순한 구조로 짜인 코드입니다. 하지만 시간복잡도를 계산해 봅시다.
상하좌우 및 대각선으로 후보의 수를 계산해야 하기 때문에 Worst case가 8의 N-1승이 될 수가 있습니다. 최악이군요!

##### 이론적 배경: 재귀 호출과 부분 문제
------------------------------
재귀 호출을 공부하면서 배워야 할 개념인 문제(problem)와 부분문제(sub problem)의 정의에 대해 알아보자고 합니다. 
뒤의 동적 계획법이나 분할 정복과 같은 중요한 디자인 패러다임을 설명하는 데 사용되는데, 쉽게 생각할 수 있는 직관과는 약간 차이가 있습니다.

문제는 항상 수행해야 할 작업과 그 작업을 적용할 자료의 조합을 의미합니다. 
(1,2,3)과 (3,2,1)을 오름차순으로 정렬하라는 것중 후자만 문제이다.

부분 문제란 원래 문제에서 조각을 떼어냈을 뿐 형식이 같은 또 다른 문제를 푼 결과이다.
보글 게임에서 재귀를 타고 넘어가는 경우를 생각하면 이해가 쉽습니다.


### 최적화 문제
---------------------------------------------
최적화 문제는 여러가지 방법 중에 특정 기준에 가장 적합한 답을 고르는 문제입니다. 
해당 문제가 가장 적합한 지를 어떻게 알 수 있을까요?
동적 계획법, 조합 탐색 같은 애들이 존재하지만 제일 심플한 방법은 역시 모두 계산하는 것입니다. 

#### 예제 : 여행하는 외판원
---------------------------------------------------------
엄청나게 유명한 문제인 여행하는 외판원 문제가 있습니다. 
한 영업 사원이 한 도시에서 출발해 다른 도시들을 전부 한 번씩 방문한 뒤 돌아오려고 합니다. 가장 짧은 경로를 찾는 것이 목표입니다.

도시가 10개 있다고 가정하고 무식하게 풀어봅시다.
경로의 시작점을 고려하지 않고 계산하므로 (n-1)! 도시가 10개이면 362880개가 됩니다. 도시의 수가 늘어난다면 지금 이 풀이로는 큰일이지만 10개까진 컴퓨터는 순식간에 풀 수 있으므로 이대로 해봅시다.


#### 재귀 호출을 통한 답안 생성
-------------------------------------------
```C++
int n; //도시의 수
double dist[MAX][MAX]; //두 도시 간의 거리를 저장하는 배열
//path: 지금까지 만든 경로
//visited: 각 도시의 방문 여부
//currentLength: 지금까지 만든 경로의 길이

double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength){
    if(path.size() == n) return currentLength + dist[path[0]][path.back()]//base case: N이 되었다는건 모두 순회했다는 의미.

    double ret = INF;

    for(int next = 0; next < n; ++next){
        if(visited[next]) continue;
        int here = path.back();
        path.push_back(next);
        visited[next] = true;

        double cand = shortestPath(path,visited,currentLength + dist[here][next])
        
        ret = min(ret, cand);
        visited[next] = false;
        path.pop_back();
    }
    return ret;
}
```

### 많이 등장하는 완탐 유형
- 모든 순열 만들기
- 모든 조합 만들기
- 2의 n승 만들기





### 문제 정하기.
-----------------------------------------------------------------
김재헌:
김하진:
박진영:
서민혁:
유태정:
이성구:
이재혁: