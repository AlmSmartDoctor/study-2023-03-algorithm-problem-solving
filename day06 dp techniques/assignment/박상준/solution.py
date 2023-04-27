# 풀이 1 : 나의 풀이
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        profit_cache = [0]
        buy_price = 10 ** 4 + 1
        sell_price = -1

        for p in prices:
            buy_price = min(buy_price, p) 
            
            # p를 샀을 경우 -> 초기화 작업 진행하기
            if p == buy_price:
                sell_price = -1
            # p를 사지 않았을 경우 -> p에 팔지 말지 결정하기 
            else: 
                sell_price = max(sell_price, p)
                profit_cache.append(max(profit_cache[-1], sell_price - buy_price))
                
        return profit_cache[-1]
    
    

###########################################################    

    

# 풀이 2 : 가장 인기있는 풀이
class Solution:
    def maxProfit(self,prices):
        left = 0 #Buy
        right = 1 #Sell
        max_profit = 0
        while right < len(prices):
            currentProfit = prices[right] - prices[left] #our current Profit
            if prices[left] < prices[right]:
                max_profit =max(currentProfit,max_profit)
            else:
                left = right
            right += 1
        return max_profit