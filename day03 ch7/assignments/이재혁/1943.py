# https://www.acmicpc.net/problem/1493

import sys
input=sys.stdin.readline

l,w,h=map(int,input().split())
n=int(input())
# cubes=[[5,2], [4,3], [3,7], ...] => 큰 것 부터 채우기 위해 내림차순으로 정렬
cubes=[list(map(int,input().split())) for _ in range(n)][::-1]

ans=0

def checkTotalVolumeIsValid(boxVolume):
  total=0
  for i in cubes:
    total+=(2**i[0])**3*i[1]
    
  return total>=boxVolume


def fill(ll,ww,hh):
  global ans
  
  # base case : 채워야할 공간의 가로, 세로, 높이 중 하나로도 0일 경우
  if (ll==0 or ww==0 or hh==0):
    return
  
  for i in range(n):
    # 해당 큐브의 갯수가 0인 경우 다음 큐브로 채워야함
    if (cubes[i][1]==0):
      continue
    
    # 남은 큐브 중 가장 큰 큐브의 한 변의 길이
    biggest=2**cubes[i][0]

    # 한 변의 길이가 l,w,h보다 작아야 채울 수 있음
    if (biggest<=min(ll,ww,hh)):
      cubes[i][1]-=1
      ans+=1

      # 채우고 남은 공간 재귀호출
      fill(ll, ww, hh-biggest)
      fill(biggest, ww-biggest, biggest)
      fill(ll-biggest, ww, biggest)
      return 
  
  # 못채우고 for문을 빠져나오면 답X
  ans=-1  
    
def divideAndConquer():
  if (not checkTotalVolumeIsValid(l*w*h)):
    print(-1)
    return
    
  fill(l,w,h)
  print(ans)
  
divideAndConquer()




before=0

for idx,cnt in cubes:
  before*=8
  length=2**idx
  # 가장 큰 큐브로 채울 수 있는 최대 개수
  # before : 이전 단계의 큐브로 채운 부피만큼은 채울 필요 없으므로 빼줌
  cnt_limit = (l // length) * (w // length) * (h // length) - before
  cnt_limit = min(cnt,cnt_limit)
  
  ans+=cnt_limit
  before+=cnt_limit

if __name__=="__main__":  
  if(before==l*w*h):
    print(ans)
  else:
    print(-1)