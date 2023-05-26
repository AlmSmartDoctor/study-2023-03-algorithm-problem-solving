## 우선순위 큐(priority queue)

우선순위가 가장 높은 자료를 먼저 꺼냅니다.

- insert
- pop

구현

- LL: insert O(1), pop O(N)
- BST: insert O(log N), pop O(log N)
  - 그러나 하려는 일에 비해 오버 엔지니어링입니다.

## 힙(heap)

특히 대여섯 개의 변종 중 이진 힙(binary heap)을 다루고, 최대 힙(max heap)을 기준으로 설명합니다.

- Complete binary tree: 마지막 레벨을 제외한 모든 레벨이 꽉 차있고, 마지막 레벨은 왼쪽부터 순서대로 채워져야 합니다.
- 부모 노드의 값이 자식 노드보다 커야 합니다.

### 배열을 이용한 구현

생성은 무척 간단합니다.

```cpp
vector<int> heap;
```

### insert

1. 일단 complete binary tree를 만족하도록 맨 끝 레벨에 새 값을 추가
2. 추가된 노드의 값이 그것의 부모 노드의 값보다 크다면 부모 노드와 값 교체
3. 2의 조건이 만족하지 않을 때까지 2를 반복

시간복잡도: O(log N)

- 1: 보통 O(1)
- 2~3: 트리의 높이만큼 발생할 수 있으므로, O(log N)

### pop

최대 원소 찾기: `heap[0];` O(1).

최대 원소 꺼내기

1. 일단 마지막 노드를 삭제하고, 그 원소를 루트로 덮어씌웁니다.
2. 루트부터 출발해, 자식 중 더 큰 값을 부모로 올립니다.
3. 두 자손이 자신 이하의 원소를 가질 때까지 2를 반복합니다.

### 다른 연산들

힙 생성

- N개의 원소로 새 힙을 만드는 연산
- O(N)
- 그러나 N개를 꺼낼 때 O(N log N)이어서 큰 의미는 없습니다.

힙 정렬(heapsort)

- 무조건적인 시간복잡도 O(N log N), 공간복잡도 O(1)이 특징입니다.
- 그러나 퀵소트 및 변종이 너무 강력해 sort 구현체로 잘 채택되지는 않습니다.
  - https://www.baeldung.com/cs/quicksort-vs-heapsort
  - https://stackoverflow.com/questions/2467751/quicksort-vs-heapsort

힙의 원소 중 하나를 선택해 값을 증가

- 힙을 우선순위 큐로 사용하기 좋은 이유입니다.
- 다만 구현이 번거로워서 표준 라이브러리에서는 미지원합니다.

## 문제: 변화하는 중간 값(난이도: 하)

- 중간 값(단, 짝수 개일 때는 가운데 두 값중 작은 것으로)
- 수열의 크기가 1일 때부터 시작해서, 새로운 수가 추가될 때마다 중간 값이 바뀔 텐데, 그때마다 중간 값을 계산합니다.

입력 수열 생성

- 문제점: N(<=200,000)개의 수를 전부 넣을 수 없습니다.
- 시드값 a, b를 입력으로 받아, Day 2에서 했던 것처럼 난수를 직접 생성해서 쓰기로 합니다.

입력

- 테스트 케이스의 수 `C`(<=20)가 주어집니다.
- 이후 `C`줄에 걸쳐 수열의 길이 `N`, 난수 생성기의 가중치 `a`, bias `b`가 차례로 주어집니다.

```text
3
10 1 0
10 1 1
10000 1273 4936
```

출력: 각 테스트 케이스마다 한 줄에 `N`개의 중간 값의 합을 20090711로 나눈 나머지를 출력합니다.

```text
19830
19850
2448920
```

- 첫 번째 테스트 케이스는 [1983, 1983, ..., 1983] 입니다.
- 두 번째 테스트 케이스는 [1983, 1984, ..., 1992] 입니다.

## 풀이: 변화하는 중간 값

해결 방법은 여러가지가 있습니다.

- BST + treap: 이미 만들어진 게 있다면 상관이 없지만, 아니라면 구현이 귀찬타.

힙

- 숫자를 오름차순 정렬해 앞의 절반을 최대 힙에, 뒤의 절반을 최소 힙에 넣습니다.
- 홀수 개인 경우 최대 힙에 하나를 더 넣기로 합니다.
- 아래 불변식을 만족시킵니다.
  1. 최대 힙의 크기는 최소 힙의 크기와 같거나, 하나 더 큽니다.
  2. 최대 힙의 max <= 최소 힙의 min
- 이렇게 하면 최대 힙의 루트가 항상 중간값입니다.

원소 1개 추가

1. 1번 불변식을 만족시키는 방향으로 둘 중 한 힙에 추가합니다.
2. 2번 불변식이 깨졌다면 최대 힙의 max와 최소 힙의 min을 맞바꿉니다.
3. 끗(숫자가 하나만 추가됐으므로)

```cpp
int runningMedian(int n, RNG rng) {
    priority_queue<int, vector<int>, less<int>> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int ret = 0;

    for(int cnt = 1; cnt <= n; ++cnt) {
        // 1번 불변식
        if (maxHeap.size() == minHeap.size())
            maxHeap.push(rng.next());
        else
            minHeap.push(rng.next());

        // 2번 불변식
        if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
            int a = maxHeap.top();
            int b = minHeap.top();
            maxHeap.pop();
            minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }

        ret = (ret + maxHeap.top()) % 20090711;
    }

    return ret
}
```

- 구현체는 C++ STL의 힙 구현체인 `priority_queue`를 씁니다.
- 시간 복잡도 O(N log N)
- 환경에 따라 다르지만, 위의 BST 풀이보다 2~3배 정도 더 빠르게 동작합니다.

# 문제 풀이

유태정: https://www.acmicpc.net/problem/11000

김하진: https://leetcode.com/problems/merge-k-sorted-lists/

박진영:

서민혁: https://www.acmicpc.net/problem/11003

이재혁:

이성구:

김재헌:

한태혁:

박상준:

조민준: https://www.acmicpc.net/problem/3090

정준우: https://leetcode.com/problems/kth-largest-element-in-an-array/
