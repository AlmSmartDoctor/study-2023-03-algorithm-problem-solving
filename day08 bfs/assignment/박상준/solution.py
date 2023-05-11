
class Solution:
  def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
    m = len(matrix) # m은 행의 길이를 의미합니다. 
    n = len(matrix[0]) # n은 열의 길이를 의미합니다. 

    # 치트키 
    @lru_cache(maxsize=None)
    # dfs 트리를 생성합니다. matrix[i][j]가 바로 노드가 됩니다. 
    def dfs(i: int, j: int, prev: int) -> int:

      # 만약에 범위를 벗어나면 -> 0을 리턴합니다. 
      if i < 0 or i == m or j < 0 or j == n:
        return 0

      # 애초에 prev(이전 노드)보다 작은 경우에는 갈 수 없습니다 -> 0을 리턴합니다. 
      if matrix[i][j] <= prev:
        return 0

      # 앞선 두 경우를 제외하면 갈 수 있는 노드입니다. 
      # 이 노드를 간 다음, 현재 노드(curr)를 해당 노드로 지정합니다.
      curr = matrix[i][j]

      # 현재 노드에서 갈 수 있는 방향은 총 4개가 존재합니다. 
      # 재귀적으로 전부 지난 다음, 가장 최대값을 리턴하고 거기에 + 1(현재 노드를 지남)을 합니다.
      return 1 + max(dfs(i + 1, j, curr),
                     dfs(i - 1, j, curr),
                     dfs(i, j + 1, curr),
                     dfs(i, j - 1, curr))

    # 모든 노드를 돌면서 다음과 같은 식을 반복합니다. 
    # 첫 번째 노드는 무조건 방문해야 합니다 -> 3번째 인자를 -math.inf로 설정합니다. 
    return max(dfs(i, j, -math.inf) for i in range(m) for j in range(n))

