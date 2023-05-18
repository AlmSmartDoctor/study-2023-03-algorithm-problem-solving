# [7662. 이중 우선순위 큐](https://www.acmicpc.net/problem/7662)

제목에 *우선순위 큐*라고 적혀있지만 우선순위 큐는 못 씁니다.

앞과 뒤 양 쪽으로 원소가 삭제되기 때문입니다.

최대힙과 최소힙을 이용하여 구분지어 처리하면 되지 않을까 싶지만,

그러면 처리가 꽤나 복잡해질겁니다.

무엇보다 이번 문제풀이 주제는 BST였기 때문에 `map`으로 풀어야겠다 싶었습니다.

`map`은 key-value 구조로, key는 unique하며 이를 기준으로하여 bst 형태로 정렬돼 있습니다.

기본적으로 int 형식에 대해서는 key의 오름차순으로 정렬됩니다.

---

이 문제 풀이의 구현은 간단합니다.

1. 입력이 "I"라면 주어진 원소 N을 컨테이너에 `insert`한다.
2. 입력이 "D"라면 최소값\(begin\) 혹은 최대값\(end - 1\)을 `erase`한다.

다만 `map`에서는 unique한 key만을 다루기 때문에 같은 값이 들어왔을 때 처리가 필요합니다.

따라서 이 때, value에는 해당 값의 개수를 저장합니다.

개수가 2개 이상일 때 삭제 처리는 단지 value를 1만큼 감소시킬 뿐이고,

개수가 1일 때여야지 실제로 원소가 삭제되도록 하면 됩니다.

[`map` 구현 코드보기](7662-1.cc)

그런데 사실 C++ STL에서는 `multiset`이라는 자료구조도 제공합니다.

> Use of **`std::multiset`** instead of `std::map`:
> 
> **`std::multiset`** can be used when we want to keep the count of elements and also keep them sorted.
> 
> It automatically sorts the keys and allows duplicate keys.
>
> *By GPT*

`multiset` 자료구조는 중복 키를 허용하며 `map`과 동일하게 BST로 구현돼 있습니다.

문제풀이시 `map`을 사용했을 때보다 더 간결해집니다.

[`multiset` 구현 코드 보기](7662-2.cc)

---

<img width="700px" src="imgs/Screenshot%202023-05-18%20at%2021.11.05.JPG" />

아래가 map 구현, 위에가 multiset 구현입니다.

이론상 시간복잡도는 동일하나, 시간은 multiset이 더 오래 걸립니다.

map과 multiset 모두 RB Tree로 구현됐다고 하는데 의문입니다.