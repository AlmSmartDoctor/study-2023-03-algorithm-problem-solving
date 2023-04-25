# dynamic programming techniques

# 1. 최적화 문제의 실제 답 계산하기 (279p)
  모든 부분 문제에 대해서 최적해를 저장하는 경우 메모리를 많이 차지하고 번거롭다
  때문에 동적 계획법을 사용 할 경우 실제 최적해를 구하는 과정은 별도로 구현
  각 부분에서 어떤 선택을 해야 최적해가 나오는지 기록, 별도의 재귀 함수를 사용해서 최적해를 생성

  꼭 재귀 함수를 사용 할 필요는 없지만 메모이제이션을 사용하는 함수와 구조가 비슷하기 때문에 재귀 호출을 이용하는 쪽이 편리함

  요약
  1. 재귀 호출의 각 단계에서 최적해를 만들었던 선택을 별도의 배열에 저장
  2. 별도의 재귀 함수를 이용해서 선택을 따라가며 각 선택지를 저장해서 출력

# 2. k번째 답 계산하기 (293p)
  
    K번째 답을 구해야 하는 경우

    현재까지 M개를 스킵하고 다음 선택을 하면 N개가 스킵되는 경우(M <= K)
    
    N >= K - M 인 경우 해당 선택을 하면 안됨

    N < K - M 인 경우 해당 선택지 선택

    선택 한 경우 M += N, 반복

  ## 예제: N 번째 자연수를 찾는 문제를 생각해보자
  

# 3. 정수 이외의 입력에 대한 메모이제이션 (312p)

  메모이제이션으로 최적화하려고 할 때 입력이 정수가 아닌 경우 

  1. 연관 배열 사용하기 

    python dictionary, c++ map 사용
    A["first"] = 1, A["second"] = 39
  

  2. 일대일 대응 함수 작성하기

    1. 입력이 순열인 경우
      주어지는 배열이 [1, 2, 3] 의 순열(Permutation) 일 때 가능한 경우는
        [1, 2, 3] => 0
        [1, 3, 2] => 1
        [2, 1, 3] => 2
        [2, 3, 1] => 3
        [3, 1, 2] => 4
        [3, 2, 1] => 5
      가능한 모든 배열을 순서대로 정렬해서 숫자에 대응

    2. 입력이 bool 값 배열인 경우
      false, true 를 각각 0, 1에 대응해서 2진수로 치환
      [true, false, false, true] = 1001(2) = 9
      [true, true, false, false] = 1100(2) = 12
      
    3. 입력의 범위가 좁은 경우
      위와 비슷하게 입력이 0 ~ K - 1 사이의 값을 원소로 갖는 길이 N의 배열인 경우
      N 자리의 K 진수로 치환 가능하다


# 4. 조합 게임 (333p)
  
|||||||||
|-|-|-|-|-|-|-|-|
| |O| | | | | | |
| | |X|★|X| | | |
|O|X|X|X| | |O| |
| | |O|O|X| | | |
| | |X| |O| | | |
| | |O| | | | | |

오목에서는 별표 표시된 자리에 X가 놓아야 완벽한 수(Perfect Move)가 된다

그러면 이런 '완벽한 수' 를 어떻게 찾을까?

상태와 차례가 주어질 때 해당 차례의 플레이어가 이길 수 있는지를 재귀 함수를 만들어서 해결


## 예제: Tic Tac Toe (337p)
```c++
// turn 이 한 줄을 만들었는지를 반환한다.
bool isFinished(const vector<string>& board, char turn);

// 틱택토 게임판이 주어질 때 [0, 19682] 범위의 정수로 변환한다
// 19683 == 3 ^ 9
int bijection(const vector<string>& board) 
{
  int ret = 0;
  for (int y = 0; y < 3; ++y)
  {
    for (int x = 0; x < 3; ++x)
    {
      ret = ret * 3;
      // 비어있는 경우 0, o 인 경우 1, x 인 경우 2
      // 9자리 3진수의 숫자 형식으로 변환
      if (board[y][x] == 'o') ret += 1;
      else if (board[y][x] == 'x') ret += 2;
    }
  }
  return ret;
}

// cache[] 는 -2로 초기화
int cache[19683];

// 현재 차례가 이길 수 있으면 1, 비길 수 있으면 0, 지면 -1을 리턴
int canWin(vector<string>& board, char turn)
{
  // 기저 사례: 마지막에 상대가 둬서 한 줄이 만들어진 경우
  if (isFinished(board, 'o' + 'x' - turn)) return -1;
  int& ret = cache[bijection(board)];
  if (ret != -2) return ret;
  
  int minValue = 2;
  // 지금 비어있는 모든 칸에 대해서 한번씩 체크한다
  for (int y = 0; y < 3; ++y)
  {
    for (int x = 0; x < 3; ++x)
    {
      if (board[y][x] == '.')
      {
        board[y][x] = turn;
        minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
        board[y][x] = '.';
      }
    }
  }

  // 플레이할 수 없거나, 어떻게 해도 비기는 것이 최선인 경우
  if (minValue == 2|| minValue == 0) return ret = 0;

  // 최선이 상대가 이기는 거라면 현재 차례는 무조건 지고, 상대가 지는 것이면 무조건 이긴다.
  return ret = -minValue;
}
```

틱택토 문제의 경우 3 ^ 11 = 177147 정도로 경우의 수가 적어서 더 최적화를 하지 않아도 해결 가능<br>
경우의 수가 더 큰 경우 중복을 추가로 더 제거하거나 문제에 맞게 최적화를 해 주어야 함



# 5. 반복적 동적 계획법 (349p)
  > 부분 문제 간의 의존성을 파악하기 쉬운 경우에는 재귀 함수가 아니라 반복문을 이용해서 동적 계획법을 구현 가능

### 예제: Fibonacci
```c++
void int recursive(int n)
{
  if (cache[n] != 0) return cache[n];
  return recursive(n - 1) + recursive(n - 2);
}

void int repeat_sliding_window(int n)
{
  int a, b, c;
  a = 0;
  b = 1;
  for (int i = 0; i < n; i++)
  {
    c = a + b;
    a = b;
    b = c;
  }
  return a;
}

void int repeat_matrix_multiplication(int n)
{
  matrix a = {{0, 1}}; // 1 * 2 matrix

  matrix b = {{0, 1},
              {1, 1}} // 2 * 2 matrix
  
  matrix c = a * (b ^ n); // 행렬의 곱셈은 결합법칙이 성립한다

  return c[0][0];
}
```

  ### 반복적 동적 계획법과 재귀적 동적 계획법의 비교
  
| |반복적 동적 계획법|재귀적 동적 계획법|
|---|--|--|
|장점|보통 구현이 짧다|더 직관적인 코드|
|장점|재귀 호출에 비해서 더 빠르다|전체 부분 문제 중 일부의 답만 필요할 경우 더 빠르게 동작|
|장점|슬라이딩 윈도 기법을 사용 가능|부분 문제 간의 의존 관계나 계산 순서에 대해 고민할 필요가 없다|
|단점|구현이 비직관적|슬라이딩 윈도 기법 사용 불가
|단점|부분 문제 간의 의존 관계를 고려해 계산 순서를 고민해야 한다|스택 오버플로를 조심해야 한다|



# 문제 풀이

유태정: https://www.acmicpc.net/problem/11066

김하진: 

박진영: https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/
                                                                  
서민혁: https://www.acmicpc.net/problem/10273

이재혁: https://www.acmicpc.net/problem/1099

이성구: https://www.acmicpc.net/problem/2294 OR https://www.acmicpc.net/problem/2293

김재헌: https://www.acmicpc.net/problem/2695

한태혁: https://leetcode.com/problems/minimum-operations-to-reduce-an-integer-to-0/

박상준: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
