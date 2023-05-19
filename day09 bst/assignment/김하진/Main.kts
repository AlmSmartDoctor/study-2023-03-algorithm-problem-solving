class Solution {
    fun numTrees(n: Int): Int {
        val dp = IntArray(n + 1)
        dp[0] = 1
        (1..n).forEach { i ->
            dp[i] = (0 until i).fold(0) { acc, j ->
                acc + dp[j] * dp[i - j - 1]
            }
        }
        return dp[n]
    }
}