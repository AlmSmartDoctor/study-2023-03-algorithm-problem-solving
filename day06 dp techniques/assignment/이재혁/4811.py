import sys

input = sys.stdin.readline

lst = []
n = int(input())

while n != 0:
    lst.append(n)
    n = int(input())


def solve(n):
    cache = [[0] * (n + 1) for _ in range(n + 1)]
    # 남은 약이 다 반개 짜리면 경우의 수 = 1
    for i in range(n + 1):
        cache[0][i] = 1

    for i in range(1, n + 1):
        for j in range(n):
            cache[i][j] = cache[i - 1][j + 1] + cache[i][j - 1]

    # cache[n][0] == cache[n-1][1]
    return cache[n][0]

# run
if __name__ == "__main__":
    for i in lst:
        print(solve(i))
