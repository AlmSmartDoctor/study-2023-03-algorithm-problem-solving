# https://www.acmicpc.net/problem/16562
import sys

input = sys.stdin.readline


def find(x, parent):
    if x == parent[x]:
        return x

    parent[x] = find(parent[x], parent)
    return parent[x]


def union(x, y, parent):
    x, y = find(x, parent), find(y, parent)

    if parent[x] <= parent[y]:
        parent[y] = x
    else:
        parent[x] = y


if __name__ == "__main__":
    N, M, k = map(int, input().split())
    money = [0] + list(map(int, input().split()))
    tree = list(range(N + 1))
    ans = [0 for _ in range(N + 1)]

    for _ in range(M):
        v, w = map(int, input().split())
        union(v, w, tree)

    for i in range(len(tree)):
        root = tree[i]
        if not ans[root]:
            ans[root] = money[i]
            continue
        if ans[root] > money[i]:
            ans[root] = money[i]
            continue

    if sum(ans) <= k:
        print(sum(ans))
    else:
        print("Oh no")