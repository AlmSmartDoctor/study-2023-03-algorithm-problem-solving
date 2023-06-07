class OptimizedDisjointSet:
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.rank = [1] * n

    def find(self, u: int) -> int:
        if u == self.parent[u]: return u
        self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def merge(self, u: int, v: int):
        u = self.find(u)
        v = self.find(v)

        if u == v: return
        if self.rank[u] > self.rank[v]: u, v = v, u
        self.parent[u] = v
        if self.rank[u] == self.rank[v]: self.rank[v] += 1

class Solution:
    def distanceLimitedPathsExist(self, n: int, edgeList: List[List[int]], queries: List[List[int]]) -> List[bool]:
        queries = sorted((w, p, q, i) for i, (p, q, w) in enumerate(queries))
        edgeList = sorted((w, u, v) for u, v, w in edgeList)
        
        ds = OptimizedDisjointSet(n)
        answers = [None] * len(queries)

        j = 0
        for i in range(len(queries)):
            w, u, v, k = queries[i]
            while j < len(edgeList) and edgeList[j][0] < w: 
                ww, uu, vv = edgeList[j]
                ds.merge(uu, vv)
                j += 1
            answers[k] = ds.find(u) == ds.find(v)

        return answers 