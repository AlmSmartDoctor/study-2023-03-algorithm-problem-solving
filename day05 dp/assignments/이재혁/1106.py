import sys
import math
input=sys.stdin.readline
sys.setrecursionlimit(10**4)

C,N=map(int,input().split())

info=[tuple(map(int,input().split())) for _ in range(N)]
info.sort(key=lambda x:x[0])
# info = [(1, 2), (3, 4), (4, 9), (8, 7), (9, 11), (9, 8)]

# cache[n] = 고객 n명을 확보하는데 필요한 최소 비용을 저장
cache=[0] + [info[0][0] for _ in range(info[0][1])] + [math.inf]*(C-info[0][1])
# cache = [0, 1, 1, inf, inf, inf, ...]

def calcMinimumPrice(toGet):
  if (cache[toGet] != math.inf):
    return cache[toGet]
  
  for i,j in info:
    # i => j만큼의 손님을 얻기위해 필요한 금액

    # 손님을 모두 확보했으면
    if (toGet-j <= 0):
      # min(기존 값, i)로 cache set 후 break
      cache[toGet] = min(cache[toGet],i)
      break
    # 손님을 모두 확보할 때 까지 재귀 호출 후
    val = calcMinimumPrice(toGet-j) + i
    # min(기존 값, val)로 cache set
    cache[toGet] = min(cache[toGet],val)
  
  return cache[toGet]

if __name__=="__main__":
  calcMinimumPrice(C)
  print(cache[-1])