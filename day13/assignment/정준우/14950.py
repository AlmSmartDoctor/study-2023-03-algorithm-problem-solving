import sys
sys.setrecursionlimit(10**9)
input = sys.stdin.readline

def find(p, x):
    if p[x] != x:
        p[x] = find(p, p[x])
    return p[x]

def union(p, a, b):
    a, b = find(p, a), find(p, b)
    if a < b: p[b] = a
    else: p[a] = b

n, m, t = map(int, input().split())
p = [i for i in range(n+1)]
edges = []
for _ in range(m):
    a, b, c = map(int, input().split())
    edges.append((c, a, b))

edges.sort()
lines, result = 0, 0
for edge in edges:
    cost, a, b = edge
    if find(p, a) != find(p, b):
        union(p, a, b)
        result += cost
    if lines == n-1:
        break
print(result+((n-2)*(n-1)//2)*t)
