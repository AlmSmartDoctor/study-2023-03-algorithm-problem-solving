import sys

input = sys.stdin.readline

lst = []
n = int(input())

while n != 0:
    lst.append(n)
    n = int(input())


def solve(n):
    cache = [[0] * (n + 1) for _ in range(n + 1)]
    for i in range(n + 1):
        cache[0][i] = 1

    for i in range(1, n + 1):
        for j in range(i, n + 1):
            cache[i][j] = cache[i - 1][j] + cache[i][j - 1]

    return cache[n][n]


if __name__ == "__main__":
    for i in lst:
        print(solve(i))
