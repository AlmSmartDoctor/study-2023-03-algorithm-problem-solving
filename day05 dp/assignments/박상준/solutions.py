class Solution:
    def maxProfit(self, prices: List[int]) -> int: 
        answer = 0
        # 메모이제이션을 위한 캐시 
        cache = []

        for p in prices:
            # 만약에 캐시에 값이 없는 경우에는 값을 넣는다.
            if len(cache) == 0: 
                cache.append(p)
            else: 
                # 캐시의 가장 마지막 값은 
                # 항상 지금까지 발견된 값들 중 최소값이다.
                cache.append(min(cache[-1], p))
                
            answer = max(answer, p - cache[-1])
                    
        return answer 