// 답안 참고: https://js1jj2sk3.tistory.com/3
// 제출 코드: http://boj.kr/82f4a2c06a164211bde9f4f3c284032e

#include <iostream>
#include <limits>

using namespace std;

int T, K;
int cache[501][501];
int cost[501];
int sum[501];

int main() {
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
#endif

  cin >> T;
  while (T--) {
    // 파일의 크기를 입력 받아 저장합니다.
    cin >> K;
    for (int i = 0; i < K; i++) {
      cin >> cost[i];
    }

    // 부분합을 미리 더해둡니다.
    for (int i = 0; i < K; i++) {
      if (i != 0) {
        sum[i] = sum[i - 1] + cost[i];
      } else {
        sum[i] = cost[i];
      }
    }

    // 구간 간격이 0일 경우를 미리 계산해줍니다.
    for (int i = 0; i < K; i++) {
      cache[i][i] = cost[i];
    }

    // 구간 간격이 1일 경우도 미리 계산해줍니다.
    for (int i = 0; i + 1 < K; i++) {
      cache[i][i + 1] = cost[i] + cost[i + 1];
    }

    // 구간 간격 2부터 순회를 합니다.
    for (int interval = 2; interval < K; interval++) {
      for (int left = 0; left + interval < K; left++) {
        int right = left + interval;

        // 일단 최대값을 박습니다.
        cache[left][right] = numeric_limits<int>::max();

        // 현재 구간의 파일 용량 합입니다.
        int partialSum = left > 0 ? sum[right] - sum[left - 1] : sum[right];

        // 현재 구간을 둘로 나누는 경우를 모두 시도하여 가장 작은 비용을 찾습니다.
        for (int pivot = left; pivot < right; pivot++) {
          int leftCost = cache[left][pivot];
          int rightCost = cache[pivot + 1][right];
          int partialCost = leftCost + rightCost + partialSum;
          if (left == pivot) partialCost -= leftCost;
          if (right == pivot + 1) partialCost -= rightCost;
          cache[left][right] = min(cache[left][right], partialCost);
        }
      }
    }

    cout << cache[0][K - 1] << endl;
  }

  return 0;
}