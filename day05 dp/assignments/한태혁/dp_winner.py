class Solution:
    def FindMaxValue(self, dp, nums, start, end):
        if(start == end):
            return nums[start]

        if(dp[start][end] < -0.5):
            a = nums[start] - self.FindMaxValue(dp, nums, start+1, end)
            b = nums[end] - self.FindMaxValue(dp, nums, start, end-1)

            dp[start][end] = max(a, b)

        return dp[start][end]

    def PredictTheWinner(self, nums: List[int]) -> bool:
        dp = ([[-1] * len(nums)for _ in range(len(nums))])

        return True if self.FindMaxValue(dp, nums, 0, len(nums)-1) >= 0 else False