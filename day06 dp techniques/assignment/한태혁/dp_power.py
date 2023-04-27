" https://leetcode.com/problems/minimum-operations-to-reduce-an-integer-to-0/ "

class Solution:
    def minOperations(self, n: int) -> int:
        if n < 3: return 1

        dp = [0]
        dp.append(1)
        dp.append(1)
        for i in range(3, n + 1):
            power = math.floor(math.log2(i))

            lower = pow(2, power)
            if lower == i: 
                dp.append(1)
            else:
                upper = lower * 2
                dp.append(min([dp[i-lower], dp[upper-i]]) + 1)

        return dp[n]