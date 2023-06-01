def networkDelayTime(self, times: List[List[int]], N: int, K: int) -> int:
        graph = collections.defaultdict(list)
        for (u, v, w) in times:
            graph[u].append((v, w))
            
        priority_queue = [(0, K)]
        shortest_path = {}
        while priority_queue:
            w, v = heapq.heappop(priority_queue)
            if v not in shortest_path:
                shortest_path[v] = w
                for v_i, w_i in graph[v]:
                    heapq.heappush(priority_queue, (w + w_i, v_i))
                    
        if len(shortest_path) == N:
            return max(shortest_path.values())
        else:
            return -1