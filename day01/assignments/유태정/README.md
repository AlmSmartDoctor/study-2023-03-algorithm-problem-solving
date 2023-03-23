[1101번. 카드 정리 1](https://www.acmicpc.net/problem/1101)

예제부터 차근차근 이해를 해봅시다.

## 예제 1

| Box No. | Red | Blue |
| ------- | --- | ---- |
| 1       | 1   | 1    |
| 2       | 1   | 1    |
| 3       | 1   | 0    |

이 경우는 1번 박스를 조커로 지정하고 2번 박스의 **모든 카드**를 1번 박스로 이동합니다.

> _이동 한 번은 한 박스에서 **1장 이상**의 카드를 빼 다른 박스에 넣는 것을 의미하며, 빼낸 카드의 색상은 같지 않아도 된다._

| Box No. | Red | Blue |
| ------- | --- | ---- |
| 1*      | 2   | 2    |
| 2       | 0   | 0    |
| 3       | 1   | 0    |

> ### 출력: 1

## 예제 2

| Box No. | Red | Blue |
| ------- | --- | ---- |
| 1       | 2   | 0    |
| 2       | 1   | 1    |

2번 박스를 조커 박스로 지정하면 아무것도 안 해도 조건을 모두 만족합니다.

| Box No. | Red | Blue |
| ------- | --- | ---- |
| 1       | 2   | 0    |
| 2*      | 1   | 1    |

> ### 출력: 0

## 예제 3

| Box No. | Red | Blue |
| ------- | --- | ---- |
| 1       | 1   | 0    |
| 2       | 1   | 0    |
| 3       | 0   | 1    |
| 4       | 0   | 1    |

1번 박스를 조커 박스로 지정하고, 3번 박스의 **모든 카드**를 1번 박스로 이동합니다.

| Box No. | Red | Blue |
| ------- | --- | ---- |
| 1*      | 1   | 1    |
| 2       | 1   | 0    |
| 3       | 0   | 0    |
| 4       | 0   | 1    |

> ### 출력: 1

## 예제 4

| Box No. | Red | Blue |
| ------- | --- | ---- |
| 1       | 1   | 1    |
| 2       | 1   | 1    |
| 3       | 1   | 1    |
| 4       | 1   | 0    |
| 5       | 1   | 0    |
| 6       | 0   | 1    |

먼저, 1번 박스를 조커 박스로 지정하고 2번 박스의 **모든 카드**를 1번 박스로 옮깁니다.

| Box No. | Red | Blue |
| ------- | --- | ---- |
| 1*      | 2   | 2    |
| 2       | 0   | 0    |
| 3       | 1   | 1    |
| 4       | 1   | 0    |
| 5       | 1   | 0    |
| 6       | 0   | 1    |

그리고 3번 박스의 **모든 카드**도 1번 박스로 옮깁니다.

| Box No. | Red | Blue |
| ------- | --- | ---- |
| 1*      | 3   | 3    |
| 2       | 0   | 0    |
| 3       | 0   | 0    |
| 4       | 1   | 0    |
| 5       | 1   | 0    |
| 6       | 0   | 1    |

마지막으로, 4번 박스의 **모든 카드**까지 1번 박스로 옮깁니다.

| Box No. | Red | Blue |
| ------- | --- | ---- |
| 1*      | 4   | 3    |
| 2       | 0   | 0    |
| 3       | 0   | 0    |
| 4       | 0   | 0    |
| 5       | 1   | 0    |
| 6       | 0   | 1    |

> ### 출력: 3

---

## 풀이 전략

1. 일단 묻따말 조커 박스를 하나 지정합니다.
2. 이 때, 최대 이동 횟수는 모든 카드를 조커 박스로 이동하는 N - 1회입니다.
3. 빈 박스는 없는 셈 칩니다.
4. 한 가지 종류의 색 카드만 가진 박스도 굳이 이동할 필요가 없습니다.
5. 다만, 그러한 박스 중 같은 색의 카드를 공유하는 박스 중에서는 하나 외엔 다 이동해야겠죠.

---

## 답안

사실 스스로 풀려다가 굴복해버린 문제였습니다. OTL

```cpp
// 백준 1101번. 카드 정리 1
// 소스코드 출처: https://blog.naver.com/jinhan814/222415908801
// 코드 전문 인용 및 일부 수정을 거쳐 주석을 달았습니다.

#include <iostream>

using namespace std;

int NUMBER_OF_BOXES, NUMBER_OF_COLORS, state[50][50];

int solve() {
  int minimumNumberOfMoving = NUMBER_OF_BOXES - 1;

  // 조커 박스를 하나 씩 가정해봅니다.
  for (int jocker = 0; jocker < NUMBER_OF_BOXES; jocker++) {
    int numberOfMoving = NUMBER_OF_BOXES - 1;
    bitset<50> check;

    // 모든 박스를 순회합니다.
    for (int box = 0; box < NUMBER_OF_BOXES; box++) {
      if (box == jocker) continue;

      int numberOfColorsInBox = 0;
      int colorIndex = -1;

      // 현재 박스의 모든 색상을 순회합니다.
      for (int color = 0; color < NUMBER_OF_COLORS; color++) {
        // 현재 박스에 현재 색상의 카드가 존재합니다.
        if (state[box][color]) {
          numberOfColorsInBox++;
          colorIndex = color;
        }
      }

      // 현재 박스는 비어 있습니다.
      if (numberOfColorsInBox == 0) {
        numberOfMoving--;
      }
      // 현재 박스는 단 한 종류의 색상 카드가 있습니다.
      else if (numberOfColorsInBox == 1) {
        check[colorIndex] = 1;  // 현재 박스에 보관된 단 한 종류의 색상을 기록합니다.
      }
    }

    // 단 한 종류의 색상 카드를 지닌 박스는 그대로 두면 됩니다.
    numberOfMoving -= (int) check.count();
    minimumNumberOfMoving = min(minimumNumberOfMoving, numberOfMoving);
  }
  return minimumNumberOfMoving;
}

int main() {
  cin >> NUMBER_OF_BOXES >> NUMBER_OF_COLORS;

  for (int i = 0; i < NUMBER_OF_BOXES; i++) {
    for (int j = 0; j < NUMBER_OF_COLORS; j++) {
      cin >> state[i][j];
    }
  }

  cout << solve() << endl;
}
```