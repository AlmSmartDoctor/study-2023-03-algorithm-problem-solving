# https://leetcode.com/problems/number-of-islands/

class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        if not grid: return 0
        row = len(grid)
        col = len(grid[0])
        landCount = 0

        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j] == '1':
                    q = [(i, j)]
                    grid[i][j] = '0'
                    while q:
                        x, y = q.pop(0)
                        for moveX, moveY in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                            currentX, currentY = x + moveX, y + moveY
                            if 0 <= currentX < row and 0 <= currentY < col and grid[currentX][currentY] == '1':
                                q.append((currentX, currentY))
                                grid[currentX][currentY] = '0'
                    landCount += 1

        return landCount