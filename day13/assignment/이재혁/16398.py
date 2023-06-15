import sys
import heapq
import math

input = sys.stdin.readline
sys.setrecursionlimit(10**6)


def findParent(node, parent):
    if parent[node] != node:
        parent[node] = findParent(parent[node], parent)
    return parent[node]


def 합치기(node1, node2, parent):
    node1, node2 = findParent(node1, parent), findParent(node2, parent)

    if node1 < node2:
        parent[node2] = node1
    else:
        parent[node1] = node2


def 사이클확인(node1, node2, parent):
    node1, node2 = findParent(node1, parent), findParent(node2, parent)
    if node1 == node2:
        return True
    else:
        return False


def 크루스칼(그래프, parent):
    최소거리 = 0

    for i in 그래프:
        출발, 도착, 거리 = i
        if not 사이클확인(출발, 도착, parent):
            최소거리 += 거리
            합치기(출발, 도착, parent)

    return 최소거리


def 프림(그래프, 시작점):
    답 = 0
    큐 = []
    저장된거리 = [0] + [math.inf for _ in range(N - 1)]
    방문했는지 = [False] * N
    heapq.heappush(큐, (0, 시작점))

    while 큐:
        거리, 현위치 = heapq.heappop(큐)

        if 방문했는지[현위치]:
            continue
        if 거리 > 저장된거리[현위치]:
            continue

        방문했는지[현위치] = True
        답 += 거리

        for 다음위치 in range(len(그래프)):
            if not 방문했는지[다음위치] and 저장된거리[다음위치] > 그래프[현위치][다음위치]:
                저장된거리[다음위치] = 그래프[현위치][다음위치]
                heapq.heappush(큐, (그래프[현위치][다음위치], 다음위치))
    return 답


if __name__ == "__main__":
    N = int(input())
    arr = [list(map(int, input().split())) for _ in range(N)]
    parent = [i for i in range(N + 1)]
    graph = []

    for 출발 in range(N):
        for 도착 in range(출발 + 1, N):
            if 출발 != 도착:
                graph.append((출발, 도착, arr[출발][도착]))

    graph.sort(key=lambda x: x[2])

    # 1212 ms
    답1 = 크루스칼(graph, parent)
    # 412 ms
    답2 = 프림(arr, 0)

    print(답1, 답2)
