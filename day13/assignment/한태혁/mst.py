# https://leetcode.com/problems/min-cost-to-connect-all-points/

class Solution:
    def __init__(self):
        self.graph = defaultdict(list)
        self.selected = set()
        self.dist = []

    def addEgde(self, point):
        for edge in self.graph[point]:
            _, point = edge
            if point in self.selected:
                continue
            heapq.heappush(self.dist, edge)

    def minCostConnectPoints(self, points: List[List[int]]) -> int:
        startEdge = None
        minDist = float('inf')
        
        for i in range(len(points)):
            now = tuple(points[i])
            for j in range(i, len(points)):
                neighbor = tuple(points[j])
                absDist = abs(now[0] - neighbor[0]) + abs(now[1] - neighbor[1])
                if absDist < minDist:
                    minDist = absDist
                    startEdge = (now, neighbor)
                
                self.graph[now].append((absDist, neighbor))
                self.graph[neighbor].append((absDist, now))
        
        
        self.selected.add(startEdge[0])
        self.selected.add(startEdge[1])
        self.addEgde(startEdge[0])
        self.addEgde(startEdge[1])
        
        ret = 0
        while self.dist:
            absDist, point = heapq.heappop(self.dist)
            if point in self.selected:
                continue
            ret += absDist
            self.selected.add(point)
            self.addEgde(point)
            
        return ret