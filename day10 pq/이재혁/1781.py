# https://www.acmicpc.net/problem/1781

import sys
import heapq

input = sys.stdin.readline

N = int(input())
curTime = 0
ans = []

arr = list(tuple(map(int, input().split())) for _ in range(N))
arr.sort(key=lambda x: (x[0], -x[1]))

for problem in arr:
    time, ramenToGet = problem
    if curTime < time:
        heapq.heappush(ans, ramenToGet)
        curTime += 1
    else:
        if ans[0] < ramenToGet:
            heapq.heappop(ans)
            heapq.heappush(ans, ramenToGet)


print(sum(ans))
