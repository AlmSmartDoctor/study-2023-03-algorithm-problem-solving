# https://leetcode.com/problems/design-graph-with-shortest-path-calculator/

class Graph:

    def __init__(self, n: int, edges: List[List[int]]):
        self.adj = [[math.inf for j in range(n)] for i in range(n)]

        for i, j, k in edges:
            self.adj[i][j] = k

        for i in range(n):
            self.adj[i][i] = 0

        for k in range(n):
            for i in range(n):
                if(self.adj[i][k] < math.inf):
                    for j in range(n):
                        self.adj[i][j] = min([self.adj[i][j], self.adj[i][k] + self.adj[k][j]])

    def addEdge(self, edge: List[int]) -> None:
        n = len(self.adj)
        start, end, val = edge

        if self.adj[start][end] <= val:
            return
        
        self.adj[start][end] = val
        for k in [start, end]:
            for i in range(n):
                for j in range(n):
                    self.adj[i][j] = min(self.adj[i][j], self.adj[i][k] + self.adj[k][j])

        return
        
    def shortestPath(self, node1: int, node2: int) -> int:
        return self.adj[node1][node2] if self.adj[node1][node2] < math.inf else -1


# Your Graph object will be instantiated and called as such:
# obj = Graph(n, edges)
# obj.addEdge(edge)
# param_2 = obj.shortestPath(node1,node2)

class Graph:

    def __init__(self, n: int, edges: List[List[int]]):
        self.adj_list = [[] for _ in range(n)]
        for a, b, cost in edges:
            self.adj_list[a].append((b, cost))

    def addEdge(self, edge: List[int]) -> None:
        a, b, cost = edge
        self.adj_list[a].append((b, cost))

    def shortestPath(self, node1: int, node2: int) -> int:
        n, pq = len(self.adj_list), [(0, node1)]
        dist = [inf] * (n)
        dist[node1] = 0

        while pq:
            d, node = heappop(pq)
            if node == node2: return d
            if d > dist[node]: continue
            for neighbor, cost in self.adj_list[node]:
                new_dist = d + cost
                if new_dist < dist[neighbor]:
                    dist[neighbor] = new_dist
                    heappush(pq, (new_dist, neighbor))
        return -1