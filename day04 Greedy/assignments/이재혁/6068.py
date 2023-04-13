import sys
input=sys.stdin.readline

# https://www.acmicpc.net/problem/6068

N=int(input())

works=[tuple(map(int,input().split())) for _ in range(N)]
# 늦게 끝내도 되는 일 먼저 확인하려고 내림차순 정렬
works.sort(key=lambda x:(x[1],x[0]),reverse=True)
# works = [(5, 20), (1, 16), (8, 14), (3, 5)]

# ans = 15
ans=works[0][1]-works[0][0]

for i in range(1,N):
  # 일어나야할 시간보다 끝내야 할 일의 데드라인이 더 이르면
  if (ans > works[i][1]):
    # 일어나야할 시간 = 데드라인 - 걸리는 시간
    ans = works[i][1] - works[i][0]
  # 일어나야할 시간이 끝내야할 일의 데드라인보다 이르면
  else:
  # 일어나야할 시간 -= 그 일을 마치는데 걸리는 시간
    ans -= works[i][0]
  # 답이 음수면 끝마칠 수 없음
  if (ans < 0):
    ans=-1
    break

print(ans)