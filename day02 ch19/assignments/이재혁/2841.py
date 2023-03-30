import sys

input=sys.stdin.readline
N,P=map(int,input().split())
# 기타 줄 갯수 만큼 스택 생성
stacks=[[] for _ in range(7)]

ans=0

for i in range(N):
  lineNo,fretNo=map(int,input().split())

  # 눌러야 할 음의 줄을 잡고있지 않거나 눌러야 할 음의 프렛이 이미 잡고있는 프렛보다 큰 경우
  if (not stacks[lineNo] or (stacks[lineNo] and stacks[lineNo][-1]<fretNo)):
    stacks[lineNo].append(fretNo)
    ans+=1
    continue
  
  # 눌러야할 음을 이미 잡고있는 경우
  if (stacks[lineNo][-1]==fretNo):
    continue
  
  # 눌러야할 음의 프렛이 이미 잡고있는 프렛보다 작은 경우
  while (stacks[lineNo] and stacks[lineNo][-1]>fretNo):
    stacks[lineNo].pop()
    ans+=1
  
  if(stacks[lineNo] and stacks[lineNo][-1]==fretNo):
    continue
  
  stacks[lineNo].append(fretNo)
  ans+=1
  
print(ans)
  