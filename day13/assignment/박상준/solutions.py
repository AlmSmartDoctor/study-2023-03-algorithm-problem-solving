class Solution:
    def minCostConnectPoints(self, points: List[List[int]]) -> int:
        # d: 'key -> 좌표값 (x, y), value -> 그곳까지의 거리'인 dictionary
        # res: 정답
        # value 초기화: 인덱스 기준 처음 좌표만 '0'만 0, 나머지는 전부 무한대 
        d, res = {(x, y): float('inf') if i else 0 for i, (x, y) in enumerate(points)}, 0
        
        # d가 존재할 때까지 계속 진행
        while d:
            # d.get(value)를 기준으로 최솟값의 key를 리턴한다. 
            x, y = min(d, key=d.get)

            # 리턴된 값을 기존 딕셔너리에서 제외한다. 
            # 그리고 그 value를 res에 더한다. 
            res += d.pop((x, y))

            # 다음 지점의 맨해튼 거리를 갱신한다. 
            # 기존의 길이가 더 짧음 -> 그냥 내비둠 
            # 기존의 길이가 더 김 -> x, y를 거쳤을 때의 거리로 바꿈
            for x1, y1 in d:
                d[(x1, y1)] = min(d[(x1, y1)], abs(x-x1)+abs(y-y1))
            
        return res