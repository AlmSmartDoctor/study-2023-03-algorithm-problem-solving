class Solution {
    private val dp: HashMap<TreeNode, Pair<Int, Int>> = hashMapOf() // TreeNode의 왼쪽으로 방향으로의 최댓값/ 오른쪽으로의 최댓값

    fun longestZigZag(root: TreeNode?): Int {
        return dfs(root)
    }

    private fun dfs(root: TreeNode?): Int {
        if (root == null) return 0
        if (root.left == null && root.right == null) {
            dp[root] = Pair(0, 0)
            return 0
        }

        val leftMax = dfs(root.left) // 왼쪽 child node의 최대 경로 수 (현재 노드 제외)
        val rightMax = dfs(root.right) // 오른쪽 child node의 최대 경로 수 (현재 노드 제외)

        val `root to left to right` = //root -> root.left -> root.left.right
            if (root.left != null && dp[root.left] != null) dp[root.left]?.second?.plus(1) ?: 0
            else 0

        val `root to right to left` = //root -> root.right -> root.right.left
            if (root.right != null && dp[root.right] != null) dp[root.right]?.first?.plus(1) ?: 0
            else 0

        dp[root] = Pair(`root to left to right`, `root to right to left`)

        return leftMax
            .coerceAtLeast(rightMax)
            .coerceAtLeast(`root to left to right`)
            .coerceAtLeast(`root to right to left`)
    }
}