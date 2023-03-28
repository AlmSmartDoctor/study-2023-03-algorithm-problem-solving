# Ch. 19 - 큐와 스택, 데크

큐, 스택, 데크는 배열과 연결 리스트로 쉽게 구현할 수 있습니다.  
하지만 중요한 점은, 흔히 사용되는 자료 구조에 이름을 붙였다는 점입니다.  
의사소통이 더 쉬워지고, 프로그램 설계 시 추상화를 통한 이점을 얻을 수 있습니다.  


## 19.1 자료구조 설명

큐

- Queue, FIFO (first in, first out), FCFS (first-come, first-served)
- 가장 먼저 들어간(push) 데이터를 가장 먼저 꺼냄(pop)
- job scheduling 등에서 자주 사용

스택

- Stack, LIFO (last in, first out)
- 가장 늦게 들어간 데이터를 가장 먼저 꺼냄
- 함수의 호출 스택 관리를 스택으로 함

데크

- Dequeue, double-ended queue, deque
- 양쪽으로 넣고 꺼냄
- 데크가 구현되어 있다면 스택, 큐를 모두 구현할 수 있음

## 19.2 구현

연결 리스트

- 구현이 간단함 (그냥 list 하나만 delegate하면 됨)
- Doubly-linked list 이용 시 삽입, 삭제 O(1)
- 그냥 N개 순차 순회도 O(N)
- 단, random access 시 O(N)
- 중간에 있는 값에 무언가를 하지 않는다면 아주 훌륭한 선택

배열

- 문제 1: 앞에서부터 데이터를 지우면 빈
- 문제 2: 배열 크기가 꽉 차면 재할당을 해야 한다

Dynamic Array† + Circular Buffer

![tail과 head가 반대로 된 그림](https://ars.els-cdn.com/content/image/3-s2.0-B9780128037614000083-f08-04-9780128037614.jpg)

- 2권 627쪽 그림 19.1 참조
- circular buffer 테크닉으로 공간을 재활용
- 배열이 모두 차면 dynamic array 테크닉으로 배열 확장
- 최종적으로 삽입, 삭제, random access 모두 최적화 가능

†동적 배열, Ch. 18 참조

## 19.3 활용

- 조세푸스의 문제(18.3절)
- 울타리 자르기(7장)
- 둘 다 아직 안 했는데?

## 19.4, 19.5 문제: 짝이 맞지 않는 괄호 (BRACKETS2, 하)

- 소괄호, 중괄호, 대괄호로만 이루어진 문자열이 주어질 때, 해당 문자열의 괄호들이 짝이 맞는지 판단
- let Σ = {'(', ')', '{', '}', '[', ']'}
- let L = Σ＊
- 입력: L에 속하는 아무 문자열 N개
- 출력: 각 문자열이 짝이 맞는지 여부를 순차적으로 출력
- 스택으로 간단하게 해결 가능

## 19.6 문제: 외계 신호 분석 (ITES, 중)

문제

- N개의 "입력 신호"로 이루어진 입력 신호 수열 I가 주어질 때, 합이 K인 부분 수열의 개수를 구하고자 함
- N = 8, I = {1, 4, 2, 1, 4, 3, 1, 6}, K = 7인 부분 수열은 다음과 같음
  - {1, 4, 2}
  - {4, 2, 1}
  - {2, 1, 4}
  - {4, 3}
  - {1, 6}

입력 생성 규칙

- 모든 입력을 다 넣기에는 입력 버퍼가 폭발할 수도 있으니, 아래의 난수 생성 규칙을 따라 입력 신호를 직접 계산해서 사용할 것
- 입력 신호 수열 I와 난수 생성 수열 A에 대해
- A[0] = 1983
- A[i] = (A[i-1] * 214013 + 2531011) % (1 << 32)
- I[i] = A[i-1] % 10000 + 1
- 이때 1 <= i <= N

제한사항

- 10초, 64MB 메모리

입력

- 테스트 케이스 개수 1 <= C <= 20
- C개의 1 <= K <= 5000000, 1 <= N <= 50000000

출력

- 각 테스트 케이스마다 첫 N개의 신호 중 합이 K인 구간의 수를 출력

예시 입출력

```text
3
8791 20
5265 5000
3578452 5000000
```

```text
1
4
1049
```

## 19.7 풀이: 외계 신호 분석

입력의 크기

- 5천만개의 32비트 정수를 저장하는 데는 190MB가 필요
- 키가 [1. 10000]임을 이용해 16비트를 쓰더라도 64MB는 명백하게 초과
- 따라서 모든 수열을 생성하지 않고 일부 입력만을 그때그때 메모리에 올리는 online algorithm을 이용해야 함
- 참고: offline algorithm은 모든 입력을 다 가지고 있다고 가정하는 알고리즘

오프라인 알고리즘 설계

- 일단 점진적으로 최적화하기로 가정하면 문제는 아주 간단해짐
- head를 맨 앞에서부터 시작해서 순회
- 현재 head부터 K를 초과할 때까지의 부분합을 구해서 매번 판단

```c++
int simple(const vector<int>& signals, int k) {
    int ret = 0;
    for (int head = 0; head < signals.size(); ++head) {
        int sum = 0;
        for (int tail = head; tail < signals.size(); ++tail) {
            sum += signals[tail];
            if (sum == k) ++ret;
            if (sum >= k) break;
        }
    }
    return ret;
}
```

- 시간 복잡도 O(NK) 로 명백히 초과, 메모리도 초과
- 다만 이 풀이를 이해하면 선형 시간 online 알고리즘으로 최적화할 수 있음

```c++
int optimized(const vector<int>& signals, int k) {
    int ret = 0, tail = 0, rangeSum = signals[0];
    for (int head = 0; head < signal.size(); ++head) {
        // rangeSum이 k 이상인 최초의 구간을 만날 때까지 tail을 옮긴다.
        while (rangeSum < k && tail + 1 < signals.size())
            rangeSum += signals[++tail];

        if (rangeSum == k) ++ret;

        // signals[head]는 이제 구간에서 빠진다.
        rangeSum -= signals[head];
    }
    return ret;
}
```

- 투 포인터
- 현재 구간의 합이 K보다 작다면 tail을 옮겨서 구간의 합을 increase
- 현재 구간의 합이 K보다 크다면 head를 옮겨서 구간의 합을 decrease
- 이렇게 하면 head와 tail의 이동이 최대 N번 발생하므로, 선형시간이 된다!

온라인 알고리즘 만들기

- 모든 데이터를 미리 생성할 필요는 없고, 새 숫자가 필요할 때마다 즉석으로 생성
- 큐를 이용해서 필요 없어진 숫자는 pop

```c++
int countRanges(int k, int n) {
    RNG rng; // 신호값을 생성하는 난수 생성기
    queue<int> range; // 구간에 있는 숫자들을 저장하는 큐
    int ret = 0, rangeSum = 0;
    for (int i = 0; i < n; ++i) {
        // 구간에 숫자를 추가
        int newSignal = rng.next();
        rangeSum += newSignal;
        range.push(newSignal);

        // 구간에서 필요 없어진 숫자를 제거
        while (rangeSum > k) {
            rangeSum -= range.fromt();
            range.pop();
        }

        if (rangeSum == k) ++ret;
    }
    return ret;
}
```

신호의 생성

```c++
struct RNG {
    unsigned seed;
    RNG() : seed(1983) {}
    unsigned next() {
        unsigned ret = seed;
        seed = ((seed * 214013u) + 2531011u);
        return ret % 10000 + 1;
    }
}
```

- 자주 사용되는 선형 합동 난수 생성기 패턴이니 참고

