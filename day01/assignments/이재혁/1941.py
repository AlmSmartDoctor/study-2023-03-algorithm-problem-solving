import sys
input=sys.stdin.readline
from collections import deque

graph=[list(input().strip()) for _ in range(5)]
dx,dy=[0,0,-1,1],[1,-1,0,0]
visited=set()

ans=0

def checkRange(x,y):
  return 0<=x<5 and 0<=y<5

def dfs(picked,S,Y):
  global ans,visited
  if(Y>3):
    return
  
  if len(picked) == 7 and S >= 4:
    picked=tuple(sorted(picked))
    if picked not in visited:
      visited.add(picked)
      ans+=1
    return
  
  for pos in picked:
        y=pos//5
        x=pos%5
        for i in range(4):
            ny,nx=y+dy[i],x+dx[i]
            n=ny*5+nx
            if checkRange(ny, nx) and n not in picked:
                picked.append(n)
                if graph[ny][nx] == 'Y':
                    dfs(picked, S, Y+1)
                else:
                    dfs(picked, S+1, Y)
                picked.pop()

for i in range(5):
    for j in range(5):
        if graph[i][j] == 'S':
            picked=[]
            picked.append(i * 5 + j)
            dfs(picked, 1, 0)
            
            
print(ans)