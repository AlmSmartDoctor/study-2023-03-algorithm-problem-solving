import sys
input=sys.stdin.readline

N=int(input())
works=[tuple(map(int,input().split())) for _ in range(N)]
works.sort(key=lambda x:(x[1],x[0]),reverse=True)
ans=works[0][1]-works[0][0]

for i in range(1,N):
  if (ans > works[i][1]):  
    ans = works[i][1] - works[i][0]
  else:
    ans -= works[i][0]
  if (ans < 0):
    ans=-1
    break

print(ans)