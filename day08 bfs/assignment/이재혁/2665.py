# https://www.acmicpc.net/problem/2665

import sys
from collections import deque

input = sys.stdin.readline

n = int(input())
maze = [list(map(int, input().rstrip())) for _ in range(n)]
visited = [[-1] * n for _ in range(n)]

dy = [1, 0, -1, 0]
dx = [0, 1, 0, -1]


def bfs():
    q = deque([(0, 0)])
    visited[0][0] = 0

    while q:
        y, x = q.popleft()

        if x == n - 1 and y == n - 1:
            print(visited[y][x])
            return

        for i in range(4):
            ny, nx = y + dy[i], x + dx[i]

            if 0 <= ny < n and 0 <= nx < n and visited[ny][nx] == -1:
                if maze[ny][nx] == 1:
                    q.appendleft((ny, nx))
                    visited[ny][nx] = visited[y][x]

                else:
                    q.append((ny, nx))
                    visited[ny][nx] = visited[y][x] + 1


if __name__ == "__main__":
    bfs()
