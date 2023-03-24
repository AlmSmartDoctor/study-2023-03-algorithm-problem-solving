import sys
input=sys.stdin.readline

# 좌석표
graph=[list(input().strip()) for _ in range(5)]
dx,dy=[0,0,-1,1],[1,-1,0,0]
ansList=set()

def checkRange(y,x):
  return 0<=x<5 and 0<=y<5

def dfs(picked,S,Y):
  global ansList
  # 임도연파가 3명이상이면 할 필요 없음
  if(Y>3):
    return
  
  # 정답을 만족하는 경우
  if len(picked) == 7 and S >= 4:
    picked=tuple(sorted(picked))
    if picked not in ansList:
      ansList.add(picked)
    return
    
  for pos in picked:
        # 5로 나눈 몫, 나머지 => 좌표 값
        y=pos//5
        x=pos%5
        for i in range(4):
            ny,nx=y+dy[i],x+dx[i]
            # n=좌석 번호
            n=ny*5+nx
            if checkRange(ny, nx) and n not in picked:
                picked.append(n)
                if graph[ny][nx] == 'Y':
                    dfs(picked, S, Y+1)
                else:
                    dfs(picked, S+1, Y)
                picked.pop()

# run
for i in range(5):
    for j in range(5):
        if graph[i][j] == 'S':
            picked=[]
            picked.append(i * 5 + j)
            dfs(picked, 1, 0)
            
            
print(len(ansList))