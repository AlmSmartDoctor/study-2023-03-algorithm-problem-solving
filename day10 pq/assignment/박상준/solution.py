# 문제 URL: https://leetcode.com/problems/find-k-closest-elements/
import heapq

# 나의 풀이
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        convert_closest = sorted([(abs(el - x), el < x, el) for el in arr], \
        key=lambda li: (li[0], not li[1]))

        convert_closest_sort = sorted([el[2] for el in convert_closest[0:k]])
        return convert_closest_sort


# 다른 풀이 보기 전에..
# 경우의 수는 총 3가지 
# 1. 점점 차이가 줄어드는 경우 
# 2. 점점 차이가 늘어나는 경우 
# 3. 점점 차이가 줄었다가 늘어나는 경우

# 투 포인터를 이용한 풀이 
class Solution:
  def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
      l, r = 0, len(arr)-k
      
      while l < r:
          # potential integer overflow를 방지하기 위해 mid를 다음과 같이 구함 
          # mid = 정답의 가장 첫 번째 인자
          mid = l + (r-l)//2

          # -3 -2 -1 0 1 2 3
          if x - arr[mid] > arr[mid+k] - x:
              l = mid+1
          else:
              r = mid

      return arr[l:l+k]


# HEAP을 이용한 풀이
class Solution:
  def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
      h = []

      for n in arr:
          if len(h) < k:
              # heapq는 최소힙, 배열의 형태로 구현되어 있음
              heapq.heappush(h, n)
          elif abs(n-x) < abs(h[0]-x):
              # 힙에 item을 푸시한 다음, heap에서 가장 작은 항목을 팝하고 반환합니다.
              heapq.heappushpop(h, n)
      
      return sorted(h)

