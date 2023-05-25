# https://leetcode.com/problems/swim-in-rising-water/

class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        n = len(grid)
        if n == 1: return 0

        pq = []
        heapq.heappush(pq, (grid[0][0], (0, 0)))
        grid[0][0] = -1
        goal = grid[n-1][n-1]
        time = 0

        while pq:
            time += 1

            while pq and pq[0][0] <= time:

                value, (x, y) = heapq.heappop(pq)
                if value == goal: return time

                for moveX, moveY in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                    currentX, currentY = x + moveX, y + moveY
                    if 0 <= currentX < n and 0 <= currentY < n and grid[currentX][currentY] != -1:
                        heapq.heappush(pq, (grid[currentX][currentY], (currentX, currentY)))
                        grid[currentX][currentY] = -1
        
        return -1